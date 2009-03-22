/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2009 Daniel Marjamäki, Reijo Tomperi, Nicolas Le Cam,
 * Leandro Penz, Kimmo Varis, Vesa Pikki
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */


//---------------------------------------------------------------------------
#ifndef CheckDangerousFunctionsH
#define CheckDangerousFunctionsH
//---------------------------------------------------------------------------

#include "check.h"

class CheckDangerousFunctionsClass : public Check
{
public:
    /** This constructor is used when registering the CheckClass */
    CheckDangerousFunctionsClass() : Check()
    { }

    /** This constructor is used when running checks.. */
    CheckDangerousFunctionsClass(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
            : Check(tokenizer, settings, errorLogger)
    { }

    void runSimplifiedChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
    {
        CheckDangerousFunctionsClass checkDangerousFunctionsClass(tokenizer, settings, errorLogger);
        checkDangerousFunctionsClass.dangerousFunctions();
    }

    /** Check for buffer overruns */
    void dangerousFunctions();

private:
    /** Error Messages.. */
    void dangerousFunctionmktemp(const Token *tok);
    void dangerousFunctiongets(const Token *tok);
    void dangerousFunctionscanf(const Token *tok);

    void getErrorMessages()
    {
        dangerousFunctionmktemp(0);
        dangerousFunctiongets(0);
        dangerousFunctionscanf(0);
    }


};

//---------------------------------------------------------------------------
#endif

