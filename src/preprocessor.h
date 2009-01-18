/*
 * cppcheck - c/c++ syntax checking
 * Copyright (C) 2007-2009 Daniel Marjamäki, Reijo Tomperi, Nicolas Le Cam
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
#ifndef preprocessorH
#define preprocessorH
//---------------------------------------------------------------------------

#include <map>
#include <istream>
#include <string>
#include <list>


class Preprocessor
{
public:
    Preprocessor();

    /**
     * Extract the code for each configuration
     * \param istr The (file/string) stream to read from.
     * \param result The map that will get the results
     */
    void preprocess(std::istream &istr, std::map<std::string, std::string> &result);

    /**
     * Extract the code for each configuration. Use this with getcode() to get the
     * file data for each individual configuration.
     *
     * @param istr The (file/string) stream to read from.
     * @param processedFile Give reference to empty string as a parameter,
     * function will fill processed file here. Use this also as a filedata parameter
     * to getcode() if you recieved more than once configurations.
     * @param resultConfigurations List of configurations. Pass these one by one
     * to getcode() with processedFile.
     */
    void preprocess(std::istream &istr, std::string &processedFile, std::list<std::string> &resultConfigurations);

    /** Just read the code into a string. Perform simple cleanup of the code */
    std::string read(std::istream &istr);

    /**
     * Get preprocessed code for a given configuration
     */
    static std::string getcode(const std::string &filedata, std::string cfg);

#ifndef UNIT_TESTING
private:
#endif

    /**
     * Remove space that has new line character on left or right side of it.
     *
     * @param str The string to be converted
     * @return The string where space characters have been removed.
     */
    static std::string removeSpaceNearNL(const std::string &str);

    /**
     * Replace "#if defined" with "#ifdef" where possible
     *
     * @param str The string to be converted
     * @return The replaced string
     */
    static std::string replaceIfDefined(const std::string &str);

    /**
     * Get all possible configurations. By looking at the ifdefs and ifndefs in filedata
     */
    std::list<std::string> getcfgs(const std::string &filedata);

    static std::string getdef(std::string line, bool def);

    static bool match_cfg_def(std::string cfg, const std::string &def);

    static std::string expandMacros(std::string code);

    /**
     * Search includes from code and append code from the included
     * file
     */
    static std::string handleIncludes(std::string code);

    /**
     * Returns the string between double quote characters.
     * @param str e.g. '#include "menu.h"'
     * @return e.g. 'menu.h' or empty string if double quotes were
     * not found.
     */
    static std::string getHeaderFileName(const std::string &str);
};

//---------------------------------------------------------------------------
#endif

