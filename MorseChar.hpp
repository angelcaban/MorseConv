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

/**
 * This class abstracts a character and its representative morse code string
 * usually in the form of dots and dashes.
 *
 * The class keeps its own internal copy of the morse code for the character,
 * and will release memory through the destructor. All instance variables
 * should not be heavily modified once this object is created. Furthermore, we
 * expect, but do not enforce, that this object is immutable.
 *
 * @note This class was tested with only ASCII c-strings.
 *
 * @todo Generalize this class to use other types of characters.
 **/
class MorseChar {
private:
    char mAscChar;
    char * mCode;

public:
    MorseChar() : mAscChar('\0'), mCode(NULL) {
    }

    /**
     * @brief Construct a MorseChar object for the given ASCII character
     *        and morse code.
     *
     * @param ascii The character which will be represented by morse code.
     * @param code  The morse code string that represents the character.
     * @param n     The size of code in characters.
     **/
    MorseChar(char ascii, const char * code, size_t n) : mAscChar(ascii), mCode(_strdup(code)) {
    }

    /**
     * @brief The copy constructor.
     *
     * @param o The constructor for which to copy from
     *
     * @note The copy constructor's purpose is to take ownership of the
     *       internal mCode pointer. This is to add efficiency to memory
     *       utilization.
     **/
    MorseChar(MorseChar & o) {
        mAscChar = o.mAscChar;
        mCode = o.mCode;
        o.mCode = NULL;
    }

    ~MorseChar() {
        free(mCode);
    }

    /**
     * @brief Set this object's ascii character
     *
     * @param ascii Usually an alpha-numeric ASCII-character.
     **/
    void setAsciiCharacter(char ascii) {
        mAscChar = ascii;
    }

    /**
     * @brief Set this object's morse code. Copies the value to our own area.
     *
     * @param code Usually a string of '.' and '-' *MUST* be NULL-terminated
     **/
    void setMorseCode(const char * code) {
        free(mCode);
        mCode = _strdup(code);
    }

    /**
     * @brief Gets the ASCII character that is represented by morse code.
     **/
    char getAsciiCharacter() const {
        return (mAscChar);
    }

    /**
     * @brief Gets the Morse Code that represents this character.
     **/
    const char * getMorseCode() const {
        return (mCode);
    }
};

#endif // MORSE_CHAR_HPP
