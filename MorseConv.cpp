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

int main(int argc, char* argv[]) {
    try {

        std::string msg;
        if (argc > 1) {
            for (int i = 1; i < argc; ++i) {
                msg.append(argv[i]);
                msg.append(" ");
            }
        } else {
            msg = "Test Message";
        }

        MorseString myMessage;
        MorseString::createFromAscii(myMessage, msg.c_str(), msg.length());
        std::cout << "Message for \"" << msg << "\" : " << std::endl;

        char resultingCode[2048];
        myMessage.toString(resultingCode, sizeof(resultingCode));
        std::cout << "    " << resultingCode << std::endl;

    } catch (std::exception & e) {

        std::cerr << "Caught exception - " << e.what() << std::endl;

    }

    (void) std::getchar();

    return 0;
}
