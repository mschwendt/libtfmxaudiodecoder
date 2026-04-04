// This is not the original script and/or version, but the old
// tfmxpack tool modified as necessary to keep compiling with
// modern C++ compilers.

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void error(const char* s1, const char* s2 = "") {
  cerr << "ERROR: " << s1 << ' ' << "'" << s2 << "'" << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        exit(-1);
    }

    ifstream fmdat( argv[1], ios::in | ios::binary | ios::ate );
    if ( !fmdat ) {
        error("Unable to access", argv[1]);
    }
    streampos lenmdat = fmdat.tellg();
    char* pmdat;
    if ( !(pmdat = new char[lenmdat]) ) {
        cerr << "ERROR: Not enough memory" << endl;
        exit(-1);
    }
    fmdat.seekg(0, ios::beg);
    fmdat.read(pmdat, lenmdat);
    if (fmdat.bad()) {
        error("Unable to access", argv[1]);
    }
    fmdat.close();

    ifstream fsmpl( argv[2], ios::in | ios::binary | ios::ate );
    if ( !fsmpl ) {
        error("Unable to access", argv[2]);
    }
    streampos lensmpl = fsmpl.tellg();
    char* psmpl;
    if ( !(psmpl = new char[lensmpl]) ) {
        cerr << "ERROR: Not enough memory" << endl;
        exit(-1);
    }
    fsmpl.seekg(0, ios::beg);
    fsmpl.read(psmpl, lensmpl);
    if (fsmpl.bad()) {
        error("Unable to access", argv[2]);
    }
    fsmpl.close();

    cout << "TFMXPAK " << lenmdat << ' ' << lensmpl << " >>>";
    cout.write(pmdat,lenmdat);
    cout.write(psmpl,lensmpl);
    cout << flush;

    delete(psmpl);
    delete(pmdat);
    return(0);
}		 
