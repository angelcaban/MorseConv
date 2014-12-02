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

#ifndef MORSE_CHAR_HPP
#define MORSE_CHAR_HPP

#include "stdafx.h"

class MorseChar {
private:
    char mAscChar;
    char * mCode;

public:
    MorseChar() : mAscChar('\0'), mCode(NULL) {
    }

    MorseChar(char ascii, const char * code, size_t n) : mAscChar(ascii), mCode(_strdup(code)) {
    }

    MorseChar(MorseChar & o) {
        mAscChar = o.mAscChar;
        mCode = o.mCode;
        o.mCode = NULL;
    }

    ~MorseChar() {
        free(mCode);
    }

    void setAsciiCharacter(char ascii) {
        mAscChar = ascii;
    }
    void setMorseCode(const char * code) {
        free(mCode);
        mCode = _strdup(code);
    }
    char getAsciiCharacter() const {
        return (mAscChar);
    }
    const char * getMorseCode() const {
        return (mCode);
    }
};

#endif // MORSE_CHAR_HPP
