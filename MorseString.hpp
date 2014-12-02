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

#ifndef MORSE_STRING_HPP
#define MORSE_STRING_HPP

#include "stdafx.h"

class MorseChar;

class MorseString {
private:
    static const unsigned SIZE_MULT;
    static MorseString POSSIBILITIES;

    MorseChar ** mBuffer;
    size_t mNumCodes;
    size_t mBufSize;

    void chkExpand();

public:

    typedef MorseChar ** _My_Type;
    typedef MorseChar * _My_Iter;

    class _iter {
    private:
        size_t __curr_idx;
        _My_Type __myT;
    public:
        _iter(_My_Type & T) : __curr_idx(0), __myT(T) {
        }
        _iter(_My_Type & T, size_t idx) : __curr_idx(idx), __myT(T) {
        }
        _iter(const _My_Type & T) : __curr_idx(0), __myT(T) {
        }
        _iter(const _My_Type & T, size_t idx) : __curr_idx(idx), __myT(T) {
        }
        void operator++ () {
            ++__curr_idx;
        }
        void operator-- () {
            --__curr_idx;
        }
        _My_Iter operator* () {
            return (__myT[__curr_idx]);
        }
        _My_Iter operator-> () {
            return (__myT[__curr_idx]);
        }
        _My_Iter operator* () const {
            return (__myT[__curr_idx]);
        }
        _My_Iter operator-> () const {
            return (__myT[__curr_idx]);
        }
        bool operator== (_iter const& lhs) {
            return (*lhs == *(*this));
        }
        bool operator!= (_iter const& lhs) {
            return (*lhs != *(*this));
        }
    };

    typedef _iter iterator;
    typedef const _iter const_iterator;
    typedef size_t size_type;

    MorseString();

    ~MorseString() {
        delete[] mBuffer;
    }

    /**
     * @brief Return a reference to a continuous string of
     *        possible Morse Code values.
     *        In order to lookup a Morse to Character
     *        conversion, use the following methods:
     *        @code{.cpp}
     *        MorseChar code;
     *        char ascii_char w = 'W';
     *        const char * morseStr = "....";
     *
     *        code = MorseString::allCodes().getByAscii(ascii_char);
     *            // code contains { 'W', ".--" }
     *        code = MorseString::allCodes().getByMorse(morseStr, sizeof (morseStr));
     *            // code contains { 'H', "...." }
     *        @endcode
     **/
    static MorseString const& allCodes();

    /**
     * @brief Add a Morse Code Character to this container.
     *        Adjusts memory allocation for internal string buffer if necessary
     *
     * @param morse A valid address to a MorseChar object.
     **/
    void add(MorseChar * morse) {
        chkExpand();
        mBuffer[mNumCodes] = morse;
        ++mNumCodes;
    }

    /**
     * @brief Gets the internal buffer of morse code characters.
     *
     * @return A constant array of pointers to MorseChar objects.
     **/
    MorseChar *const* buffer() const {
        return (mBuffer);
    }

    /**
     * @brief Gets the beginning of this string
     *
     * @return The iterator that points to the first MorseChar
     **/
    iterator begin() {
        return (iterator(mBuffer));
    }

    /**
     * @brief Gets the beginning of this string
     *
     * @return The constant iterator that points to the first MorseChar
     **/
    const_iterator begin() const {
        return (iterator(mBuffer));
    }

    /**
     * @brief Gets the end of this string (passed the last character).
     *
     * @return The iterator that points to the next memory location of the
     *         internal buffer.
     **/
    iterator end() {
        return (iterator(mBuffer, mNumCodes));
    }

    /**
     * @brief Gets the end of this string (passed the last character).
     *
     * @return The constant iterator that points to the next memory location
     *         of the internal buffer.
     **/
    const_iterator end() const {
        return (iterator(mBuffer, mNumCodes));
    }

    /**
     * @brief Return the current size of this string.
     **/
    size_type size() const {
        return (mNumCodes);
    }

    /**
     * @brief Return true if the current size of this string is 0.
     **/
    bool empty() const {
        return (mNumCodes == 0);
    }

    /**
     * @brief Looks for the character, c, in this string.
     *        The character to look for is case-insensitive.
     *
     * @param c A character to look for in this string.
     *
     * @return The MorseChar object pointer for c.
     *
     * @throws An std::out_of_range exception if this string does not contain c
     **/
    MorseChar const* getByAscii(char c) const;

    /**
     * @brief Looks for the morse code, code, in this string.
     *        Generally, the morse code MUST be a character string pointer
     *        consisting of only '.' and '-' and ' ' and possibly a NULL.
     *
     * @param code An ASCII character string representing morse code.
     * @param n The size of the code.
     *
     * @return The MorseChar object pointer for code.
     *
     * @throws An std::out_of_range exception if this string does not contain
     *         the provided morse code.
     **/
    MorseChar const* getByMorse(const char * code, size_t n) const;

    /**
     * @brief Translate this string into a series of '.' and '-' and '/' and ' '
     *        ASCII characters as a representation of this string's morse code.
     *
     * @param [out] str A valid memory location to contain the morse code result.
     * @param [in]  n   The size of str in characters.
     *
     * @note str will always return null-terminated. If str is too small for
     *       the whole message, we return only a partial result.
     **/
    void toString(char * str, size_t n) const;

    /**
     * @brief Utility method for populating a MorseString object with the
     *        corresponding MorseChar objects.
     *
     * @param [out] result This is a reference to a MorseString object to be populated.
     * @param [in]  ascii  A valid pointer to an ASCII string containing only
     *                     alpha-numeric characters.
     * @param [in]  n      The size of the 'ascii' buffer.
     *
     * @throws std::out_of_range exception if ascii contains characters that
     *         neither integers or alphabetical letters. 
     **/
    static void createFromAscii(MorseString & result, const char * ascii, size_t n);
};

#endif // MORSE_STRING_HPP
