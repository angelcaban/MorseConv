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

    static MorseString const& allCodes();

    void add(MorseChar * morse) {
        chkExpand();
        mBuffer[mNumCodes] = morse;
        ++mNumCodes;
    }

    MorseChar *const* buffer() const {
        return (mBuffer);
    }

    iterator begin() {
        return (iterator(mBuffer));
    }
    const_iterator begin() const {
        return (iterator(mBuffer));
    }
    iterator end() {
        return (iterator(mBuffer, mNumCodes));
    }
    const_iterator end() const {
        return (iterator(mBuffer, mNumCodes));
    }
    size_type size() const {
        return (mNumCodes);
    }
    bool empty() const {
        return (mNumCodes == 0);
    }

    MorseChar const* getByAscii(char c) const;
    MorseChar const* getByMorse(const char * code, size_t n) const;
    void toString(char * str, size_t n) const;

    static void createFromAscii(MorseString & result, const char * ascii, size_t n);
};

#endif // MORSE_STRING_HPP