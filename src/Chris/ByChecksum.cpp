#include "TFMXDecoder.h"

#include "MyEndian.h"
#include "CRCLight.h"
//#include "Debug.h"

void TFMXDecoder::traitsByChecksum() {
    CRCLight crc;
    smartPtr<const ubyte> sBuf(pBuf.tellBegin(),pBuf.tellLength());
    udword p0 = offsets.header + readBEudword(sBuf,offsets.patterns);
    udword crc1 = crc.get(sBuf,p0,0x100);
#if defined(DEBUG)
    cout << "CRC = " << (int)crc1 << endl;
#endif
 
    // Danger Freak (1989) seems to be a special TFMX v1 variant.
    if (crc1 == 0x48960d8c || crc1 == 0x5dcd624f || crc1 == 0x3f0b151f) {
        setTFMXv1();
        variant.noNoteDetune = true;
        variant.portaUnscaled = false;
    }
}
