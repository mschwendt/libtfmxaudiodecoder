// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "Dump.h"

#include <iostream>
#include <iomanip>
using namespace std;

void dumpLines(smartPtr<ubyte>& fcBuf, udword startOffset, sdword length, int blockLen, int index) {
    int num = 0;
    while (length > 0) {
        cout << "(0x" << hex << setw(2) << setfill('0');
        if (index>=0)
            cout << index;
        else
            cout << num;
        cout << "): ";
        num++;
        
        int b = 0;
        for (int i=0; i<blockLen; i++) {
            cout << hex << setw(2) << setfill('0')
                << (int)fcBuf[startOffset++] << " ";
            b++;
            if (b==16) {
                cout << endl;
                cout << "        ";
                b = 0;
            }
        }
        cout << endl;
        length -= blockLen;
    };
}

void dumpBlocks(smartPtr<ubyte>& fcBuf, udword startOffset, sdword length, int blockLen) {
    int num = 0;
    while (length > 0) {
        cout << "(0x" << hex << setw(2) << setfill('0') << num << "):" << endl;
        num++;
        
        int b = 0;
        for (int i=0; i<blockLen; i++) {
            cout << hex << setw(2) << setfill('0')
                << (int)fcBuf[startOffset++] << " ";
            b++;
            if (b==16) {
                cout << endl;
                b = 0;
            }
        }
        cout << endl;
        length -= blockLen;
    };
    cout << endl;
}

void dumpBytes(smartPtr<ubyte>& fcBuf, udword startOffset, int n) {
    while (n-- > 0) {
        dumpByte(fcBuf[startOffset++]);
    };
}

void dumpByte(int b) {
    cout << hex << setw(2) << setfill('0') << (b&0xff) << ' ';
}

void dumpTimestamp(udword ms) {
    udword secs = ms / 1000;
    ms %= 1000;
    udword mins = secs / 60;
    secs %= 60;
    cout << dec << setw(2) << setfill('0') << mins << ':'
         << setw(2) << setfill('0') << secs;
}
