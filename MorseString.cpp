/*
Morse Code Converter
Copyright (C) 2014 Angel Caban

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "stdafx.h"
#include "MorseChar.hpp"
#include "MorseString.hpp"

#define MORSE_A ".-"
#define MORSE_B "-..."
#define MORSE_C "-.-."
#define MORSE_D "-.."
#define MORSE_E "."
#define MORSE_F "..-."
#define MORSE_G "--."
#define MORSE_H "...."
#define MORSE_I ".."
#define MORSE_J ".---"
#define MORSE_K "-.-"
#define MORSE_L ".-.."
#define MORSE_M "--"
#define MORSE_N "-."
#define MORSE_O "---"
#define MORSE_P ".--."
#define MORSE_Q "--.-"
#define MORSE_R ".-."
#define MORSE_S "..."
#define MORSE_T "-"
#define MORSE_U "..-"
#define MORSE_V "...-"
#define MORSE_W ".--"
#define MORSE_X "-..-"
#define MORSE_Y "-.--"
#define MORSE_Z "--.."
#define MORSE_1 ".----"
#define MORSE_2 "..---"
#define MORSE_3 "...--"
#define MORSE_4 "....-"
#define MORSE_5 "....."
#define MORSE_6 "-...."
#define MORSE_7 "--..."
#define MORSE_8 "---.."
#define MORSE_9 "----."
#define MORSE_0 "-----"
#define MORSE_SPACE " "

#define __MORSE_DEF(C) MORSE_ ## C
#define MORSE_PARAMS(C) __MORSE_DEF(C), sizeof(__MORSE_DEF(C))

const unsigned MorseString::SIZE_MULT = 128;
MorseString MorseString::POSSIBILITIES;

void MorseString::chkExpand() {
    if (mNumCodes >= mBufSize) {
        mBufSize *= SIZE_MULT;

        MorseChar ** tmp = NULL;
        new (tmp) MorseChar*[mBufSize];
        for (size_t i = 0; i < mNumCodes; ++i)
            tmp[i] = mBuffer[i];

        delete[] mBuffer;
        mBuffer = tmp;
    }
}

MorseString::MorseString() : mNumCodes(0), mBufSize(SIZE_MULT) {
    mBuffer = new MorseChar*[mBufSize];
}

MorseString const& MorseString::allCodes() {
    if (POSSIBILITIES.empty()) {
        POSSIBILITIES.add(new MorseChar('A', MORSE_PARAMS(A)));
        POSSIBILITIES.add(new MorseChar('B', MORSE_PARAMS(B)));
        POSSIBILITIES.add(new MorseChar('C', MORSE_PARAMS(C)));
        POSSIBILITIES.add(new MorseChar('D', MORSE_PARAMS(D)));
        POSSIBILITIES.add(new MorseChar('E', MORSE_PARAMS(E)));
        POSSIBILITIES.add(new MorseChar('F', MORSE_PARAMS(F)));
        POSSIBILITIES.add(new MorseChar('G', MORSE_PARAMS(G)));
        POSSIBILITIES.add(new MorseChar('H', MORSE_PARAMS(H)));
        POSSIBILITIES.add(new MorseChar('I', MORSE_PARAMS(I)));
        POSSIBILITIES.add(new MorseChar('J', MORSE_PARAMS(J)));
        POSSIBILITIES.add(new MorseChar('K', MORSE_PARAMS(K)));
        POSSIBILITIES.add(new MorseChar('L', MORSE_PARAMS(L)));
        POSSIBILITIES.add(new MorseChar('M', MORSE_PARAMS(M)));
        POSSIBILITIES.add(new MorseChar('N', MORSE_PARAMS(N)));
        POSSIBILITIES.add(new MorseChar('O', MORSE_PARAMS(O)));
        POSSIBILITIES.add(new MorseChar('P', MORSE_PARAMS(P)));
        POSSIBILITIES.add(new MorseChar('Q', MORSE_PARAMS(Q)));
        POSSIBILITIES.add(new MorseChar('R', MORSE_PARAMS(R)));
        POSSIBILITIES.add(new MorseChar('S', MORSE_PARAMS(S)));
        POSSIBILITIES.add(new MorseChar('T', MORSE_PARAMS(T)));
        POSSIBILITIES.add(new MorseChar('U', MORSE_PARAMS(U)));
        POSSIBILITIES.add(new MorseChar('V', MORSE_PARAMS(V)));
        POSSIBILITIES.add(new MorseChar('W', MORSE_PARAMS(W)));
        POSSIBILITIES.add(new MorseChar('X', MORSE_PARAMS(X)));
        POSSIBILITIES.add(new MorseChar('Y', MORSE_PARAMS(Y)));
        POSSIBILITIES.add(new MorseChar('Z', MORSE_PARAMS(Z)));
        POSSIBILITIES.add(new MorseChar('1', MORSE_PARAMS(1)));
        POSSIBILITIES.add(new MorseChar('2', MORSE_PARAMS(2)));
        POSSIBILITIES.add(new MorseChar('3', MORSE_PARAMS(3)));
        POSSIBILITIES.add(new MorseChar('4', MORSE_PARAMS(4)));
        POSSIBILITIES.add(new MorseChar('5', MORSE_PARAMS(5)));
        POSSIBILITIES.add(new MorseChar('6', MORSE_PARAMS(6)));
        POSSIBILITIES.add(new MorseChar('7', MORSE_PARAMS(7)));
        POSSIBILITIES.add(new MorseChar('8', MORSE_PARAMS(8)));
        POSSIBILITIES.add(new MorseChar('9', MORSE_PARAMS(9)));
        POSSIBILITIES.add(new MorseChar('0', MORSE_PARAMS(0)));
        POSSIBILITIES.add(new MorseChar(' ', MORSE_PARAMS(SPACE)));
    }

    return (POSSIBILITIES);
}

MorseChar const* MorseString::getByAscii(char c) const {
    for (MorseChar const* mc : (*this)) {
        if (mc->getAsciiCharacter() == c) {
            return mc;
        }
    }

    std::string msg = "MorseString does not contain ";
    msg += c;
    throw (std::out_of_range(msg));
}

MorseChar const* MorseString::getByMorse(const char * code, size_t n) const {
    for (MorseChar const* mc : (*this)) {
        if (strncmp(mc->getMorseCode(), code, n) == 0) {
            return mc;
        }
    }

    std::string msg = "MorseString does not contain ";
    msg += std::string(code, n);
    throw (std::out_of_range(msg));
}

void MorseString::toString(char * str, size_t n) const {
    size_t usedSpace = 0;
    memset(str, '\0', n);

    for (MorseChar const* mc : (*this)) {
        size_t morseLen = strlen(mc->getMorseCode());
        if ((usedSpace + morseLen) >= n)
            return; // Do not overrun str

        // Append to str
        char * _tstr = str + usedSpace;
        strncpy_s(_tstr, n - usedSpace, mc->getMorseCode(), morseLen);

        // Always finish a letter with '/' unless we're printing a space.
        if (mc->getMorseCode()[0] != ' ') {
            _tstr = _tstr + morseLen;
            strncpy_s(_tstr, 2, "/", 2);
            ++morseLen;
        }

        usedSpace += morseLen;
    }
}

void MorseString::createFromAscii(MorseString & result, const char * ascii, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        char _asc = ascii[i];
        if (_asc >= 'a' && _asc <= 'z') _asc &= 0xFFDF; // to-upper-case

        MorseChar const* code = allCodes().getByAscii(_asc);
        result.add(const_cast<MorseChar *>(code));
    }
}

