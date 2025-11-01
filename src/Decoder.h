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
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef DECODER_H
#define DECODER_H

#include <string>

#include "MyTypes.h"

class PaulaVoice;

class Decoder {
public:
    Decoder();
    virtual ~Decoder() { };

    virtual void setPath(std::string pathArg) { path = pathArg; }

    virtual bool init(void*, udword, int) { return false; }
    virtual bool detect(void*, udword) { return false; }
    virtual void restart() { }
    virtual void setPaulaVoice(ubyte,PaulaVoice*) { }
    virtual int run() { return 20; }
    virtual void seek(sdword);
    
    virtual ubyte getVoices() { return 0; }
    virtual int getSongs() { return 0; }

    const std::string getFormatName() { return formatName; }
    const std::string getFormatID() { return formatID; }
    const char* getInfoString(const std::string which);
    udword getDuration() { return duration; }
    bool getSongEndFlag() { return songEnd; }
    void setLoopMode(bool x) { loopMode = x; }
    void setSongEndFlag(bool x) { songEnd = x; }
    udword getRate() { return rate; }

protected:
    void setRate(udword);  // [Hz] *256
    void setBPM(uword);

    static const std::string UNKNOWN_FORMAT_ID;
        
    std::string formatID;
    std::string formatName;
    std::string author, title, game;

    std::string path;

    bool songEnd, loopMode;
    udword duration;
    udword rate;
    udword tickFP, tickFPadd;
};

#endif  // DECODER_H
