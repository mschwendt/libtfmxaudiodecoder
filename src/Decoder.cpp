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

#include "Decoder.h"

const std::string Decoder::UNKNOWN_FORMAT_ID = "???";

Decoder::Decoder() {
    formatID = formatName = UNKNOWN_FORMAT_ID;
    duration = 0;
    songEnd = true;
    rate = 50<<8;
}

void Decoder::seek(sdword ms) {
    restart();
    while (ms>=0) {
        ms -= run();
        if ( getSongEndFlag() ) {
            break;
        }
    };
}

const char* Decoder::getInfoString(const std::string which) {
    if (which == "artist") {
        return author.c_str();
    }
    else if (which == "title") {
        return title.c_str();
    }
    else if (which == "game") {
        return game.c_str();
    }
    else {
        return 0;
    }
}

// For accuracy reasons, play speed cannot be specified as integral value,
// since 8-bit fixed point arithmetics are used.
void Decoder::setRate(udword r) {  // in [Hz]*256
    rate = r;
    tickFP = (1000<<16)/rate;  // in [ms]*256
}

void Decoder::setBPM(uword bpm) {
    setRate( ((bpm<<8)*2)/5 );
}
