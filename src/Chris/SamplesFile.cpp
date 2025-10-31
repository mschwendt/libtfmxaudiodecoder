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

#include "TFMXDecoder.h"

// Support for loading the separate file containing the samples.

#include <cstring>
#include <fstream>
using namespace std;

bool TFMXDecoder::loadSamplesFile() {
    // Got both the MDAT and SMPL file?
    if ( input.smplLoaded ) {  // if loaded before, reuse it
        input.mdatSize = input.mdatSizeCurrent;
        input.smplSize = input.smplSizeCurrent;
        return true;
    }
    if ( input.path.empty() ) {
        return false;
    }

    typedef std::pair<std::string,std::string> ExtPair;
    std::vector<ExtPair> vExtPairs = {
        { ".tfx", ".sam" },
        { ".TFX", ".SAM" },
        { ".mdat", ".smpl" },
        { ".MDAT", ".SMPL" },
        { "mdat.", "smpl." },
        { "MDAT.", "SMPL." }
    };
    for ( std::vector<ExtPair>::iterator it = vExtPairs.begin(); it != vExtPairs.end(); it++ ) {
        std::string pathSmpl = input.path;
        std::size_t found = pathSmpl.rfind(it->first);
        if (found != std::string::npos) {
            pathSmpl.replace(found,it->first.length(),it->second);
            ifstream fIn( pathSmpl, ios::in|ios::binary|ios::ate );
            if ( fIn.is_open() ) {
                //fIn.seekg(0,ios::end);
                uint32_t fLen = fIn.tellg();
                fIn.seekg(0,ios::beg);

                char* newInputBuf = new char[fLen+input.bufLen];
                memcpy(newInputBuf,input.buf,input.bufLen);
                delete[] input.buf;
                input.buf = (ubyte*)newInputBuf;

                fIn.read(newInputBuf+input.len,fLen);
                if (fIn.bad()) {
                    return false;
                }
                fIn.close();
                input.smplSize = fLen;
                input.mdatSize = input.len - offsets.header;
                offsets.sampleData = input.len;
                input.bufLen += input.smplSize;
                input.len += input.smplSize;

                // Update smart pointers.
                pBuf.setBuffer((ubyte*)input.buf,input.bufLen);
                return true;
            }
        }
    }  // next ExtPair
    return false;
}
