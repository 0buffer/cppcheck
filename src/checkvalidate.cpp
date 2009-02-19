/*
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2009 Daniel Marjamäki, Reijo Tomperi, Nicolas Le Cam,
 * Leandro Penz, Kimmo Varis
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

#include "checkvalidate.h"
#include "errorlogger.h"
#include "token.h"
#include "tokenize.h"


CheckValidate::CheckValidate(const Tokenizer *tokenizer, ErrorLogger *errorLogger)
        : _tokenizer(tokenizer), _errorLogger(errorLogger)
{

}

CheckValidate::~CheckValidate()
{

}

/**
 * Check that there are input validation when reading number from FILE/stream
 */
void CheckValidate::readnum()
{
    const Token *tok = _tokenizer->tokens();
    while (tok)
    {
        unsigned int varId = 0;

        // Search for a variable declaration
        while (tok)
        {
            if (Token::Match(tok, "int %var% ;"))
            {
                varId = tok->next()->varId();
                break;
            }
            tok = tok->next();
        }

        // Skip ahead a little with tok..
        tok = tok->tokAt(2);

        // Now take a look at the variable usage..
        if (varId == 0)
            continue;

        // Search for bad input..
        for (const Token *tok2 = tok; tok2; tok2 = tok2->next())
        {
            if (Token::Match(tok2, "cin >> %varid%", varId))
                _errorLogger->unvalidatedInput(_tokenizer, tok2);
            if (Token::Match(tok2, "fscanf ( %var% , %str% , %varid%", varId))
                _errorLogger->unvalidatedInput(_tokenizer, tok2);
            if (Token::Match(tok2, "scanf ( %str% , %varid%", varId))
                _errorLogger->unvalidatedInput(_tokenizer, tok2);
        }
    }
}


/**
 * Read data from Form/GUI
 * Todo: This function must be more customizable to be usable
 */
void CheckValidate::gui()
{
    // input control classes whose values are insecure..
    const char *inputclass[] = {"TEdit", 0};

    // functions that parse value without validating it..
    const std::string dangerousfunc("atoi|atof|strtol|strtoul");

    for (unsigned int i = 0; inputclass[i]; ++i)
    {
        const std::string classname(inputclass[i]);

        for (const Token *tok = _tokenizer->tokens(); tok; tok = tok->next())
        {
            // Declaration..
            if (Token::Match(tok, (classname + " * %var% ;|=").c_str()))
            {
                // Variable name..
                const std::string varname(tok->strAt(2));

                // Getting the value..
                const Token *tok2 = Token::findmatch(tok, (dangerousfunc + " ( " + varname + " .").c_str());
                if (tok2)
                    _errorLogger->unvalidatedInput(_tokenizer, tok2);
            }
        }
    }
}



