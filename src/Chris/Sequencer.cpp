// TFMX audio decoder library by Michael Schwendt

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, see <https://www.gnu.org/licenses/>.

#include "TFMXDecoder.h"

// TFMX's sequencer is designed as a track table with N columns (= tracks).
// Each track can assign patterns to any audio channel or execute a small
// number of commands to affect either the track or song progression.

#include "MyEndian.h"
//#include "Debug.h"

bool TFMXDecoder::getTrackMute(ubyte t) {
    return (0==readBEuword(pBuf,offsets.header+0x1c0+(t<<1)));
}

void TFMXDecoder::processTrackStep() {
    int evalMaxLoops = RECURSE_LIMIT;  // NB! Around 5 would suffice.
    do {
        sequencer.evalNext = false;

        if (sequencer.step.current > (TRACK_STEPS_MAX-1)) {  // fubar then
            sequencer.step.current = sequencer.step.first;
        }
        sequencer.stepSeenBefore[sequencer.step.current] = true;

        udword stepOffset = offsets.trackTable+(sequencer.step.current<<4);
#if defined(DEBUG_RUN)
        cout << "# Step = " << hex << setw(4) << setfill('0') << sequencer.step.current << " at 0x" << (int)stepOffset << endl;
#endif
        // 0xEFFE is the prefix of a track command.
        if ( 0xeffe == readBEuword(pBuf,stepOffset) ) {
            stepOffset += 2;
            uword command = readBEuword(pBuf,stepOffset);
#if defined(DEBUG_RUN)
            cout << "  ";
            dumpBytes(pBuf,stepOffset,2);
            cout << "  ";
#endif
            stepOffset += 2;
            if (command > TRACK_CMD_MAX) {  // fubar then
                command = 0;  // choose command "Stop" as override
            }
            trackCmdUsed[command] = true;
            (this->*TrackCmdFuncs[command])(stepOffset);
        }
        else {
#if defined(DEBUG_RUN)
            cout << "  ";
#endif
            // Set PT TR for each track.
            for (ubyte t=0; t<sequencer.tracks; t++) {
                Track& tr = track[t];
                tr.PT = pBuf[stepOffset++];
                tr.TR = pBuf[stepOffset++];
#if defined(DEBUG_RUN)
                cout << hex << setw(2) << (int)(tr.PT&255) << ' '
                     << hex << setw(2) << (int)(tr.TR&255) << " | ";
#endif
                if (tr.PT < 0x80) {
                    tr.pattern.offset = getPattOffset(tr.PT);
                    tr.pattern.step = 0;
                    tr.pattern.wait = 0;
                    tr.pattern.loops = -1;
                    tr.pattern.infiniteLoop = false;
                }
            }
#if defined(DEBUG_RUN)
            cout << endl;
#endif
        }
    }
    while ( sequencer.evalNext && --evalMaxLoops>0 );
}

void TFMXDecoder::trackCmd_NOP(udword stepOffset) {
#if defined(DEBUG_RUN)
    cout << "Track Cmd NOP" << endl;
#endif
    sequencer.step.current++;
    sequencer.evalNext = true;
}

void TFMXDecoder::trackCmd_Stop(udword stepOffset) {
#if defined(DEBUG_RUN)
    cout << "Track Cmd Stop" << endl;
#endif
    songEnd = true;
    if (loopMode) {
        restart();
    }
}

void TFMXDecoder::trackCmd_Loop(udword stepOffset) {
#if defined(DEBUG_RUN)
    cout << "Track Cmd Loop  at 0x" << (int)stepOffset << endl;
#endif
    if (sequencer.loops == 0) {  // end of loop
        sequencer.loops = -1;    // unlock
        sequencer.step.current++;
    }
    else if (sequencer.loops < 0) {  // unlocked? loop init permitted
        sequencer.step.current = readBEuword(pBuf,stepOffset);
        sequencer.loops = (sword)readBEuword(pBuf,stepOffset+2) -1;
        
        if ( (sequencer.step.current > (TRACK_STEPS_MAX-1)) ||  // fubar then
             (sequencer.step.current > sequencer.step.last) ||  // bad loop
             // Starting a loop with a negative count would be infinite.
             (sequencer.stepSeenBefore[sequencer.step.current] && sequencer.loops < 0) ) {
            songEnd = true;
            if (loopMode) {
                restart();
            }
            return;
        }
        // Limit number of loops. Only "Ramses" title sets 0xf00 and
        // seems to be the only file to set >5 loops.
        if (sequencer.loops == 0xeff) {
            sequencer.loops = 0;
        }
    }
    else {
        sequencer.loops--;
        sequencer.step.current = readBEuword(pBuf,stepOffset);
    }
    sequencer.evalNext = true;
}

void TFMXDecoder::trackCmd_Speed(udword stepOffset) {
#if defined(DEBUG_RUN)
    cout << "Track Cmd Speed" << endl;
#endif
    admin.speed = admin.count = readBEuword(pBuf,stepOffset);
    // Ignore negative values like 0xff00.
    uword arg2 = 0x81ff & readBEuword(pBuf,stepOffset+2);
    if ( (arg2 != 0) && (arg2 < 0x200) ) {
        if (arg2 < 32) {
            arg2 = 125;
        }
        setRate(arg2);
    }
    sequencer.step.current++;
    sequencer.evalNext = true;
}

void TFMXDecoder::trackCmd_Fade(udword stepOffset) {
#if defined(DEBUG_RUN)
    cout << "Track Cmd Fade  ";
    dumpBytes(pBuf,stepOffset,4);
    cout << endl;
#endif
    fadeInit(pBuf[stepOffset+3],pBuf[stepOffset+1]);
    sequencer.step.current++;
    sequencer.evalNext = true;
}

void TFMXDecoder::trackCmd_7V(udword stepOffset) {
#if defined(DEBUG_RUN)
    cout << "Track Cmd 7Voice  ";
    dumpBytes(pBuf,stepOffset,4);
    cout << endl;
#endif
    //sword arg1 = (sword)readBEuword(pBuf,stepOffset);
    sword arg2 = (sword)readBEuword(pBuf,stepOffset+2);
    if (arg2 >= 0) {
        sbyte x = (sbyte)pBuf[stepOffset+3];
        if (x < -0x20) {
            x = -0x20;
        }
        setBPM( (125*100)/(100+x) );
    }
    sequencer.step.current++;
    sequencer.evalNext = true;
}
