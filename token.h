/*
 * c++check - c/c++ syntax checking
 * Copyright (C) 2007-2008 Daniel Marjamäki and Reijo Tomperi
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

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class TOKEN
{
public:
    TOKEN();
    ~TOKEN();
    void setstr( const char s[] );

    const std::string &str() const
    { return _str; }

    const char *aaaa() const
    { return _cstr; }

    char aaaa0() const
    { return _cstr[0]; }

    char aaaa1() const
    { return _cstr[1]; }


    /**
     * Combine two tokens that belong to each other.
     * Ex: "<" and "=" may become "<="
     */
    void combineWithNext(const char str1[], const char str2[]);

    /**
     * Unlink and delete next token.
     */
    void deleteNext();

    /**
     * Returns token in given index, related to this token.
     * For example index 1 would return next token, and 2
     * would return next from that one.
     */
    const TOKEN *tokAt(int index) const;

    const char *strAt(int index) const;

    /**
     * Match given token (or list of tokens) to a pattern list.
     *
     * Possible patterns
     * "%any%" any token
     * "%var%" any token which is a name or type e.g. "hello" or "int"
     * "%num%" Any numeric token, e.g. "23"
     * "%str%" Any token starting with "-character (C-string).
     * "[abc]" Any of the characters 'a' or 'b' or 'c'
     * "int|void|char" Any of the strings, int, void or char
     * "int|void|char|" Any of the strings, int, void or char or empty string
     * "someRandomText" If token contains "someRandomText".
     *
     * The patterns can be also combined to compare to multiple tokens at once
     * by separating tokens with a space, e.g.
     * ") const|void {" will return true if first token is ')' next token is either
     * "const" or "void" and token after that is '{'. If even one of the tokens does not
     * match its pattern, false is returned.
     *
     * @param tok List of tokens to be compared to the pattern
     * @param pattern The pattern where tokens are compared, e.g. "const"
     * or ") const|volatile| {".
     * @param varname1 Used with pattern "%var1%" and "%var2%"
     * @param varname2 Used with pattern "%var1%" and "%var2%"
     * @return true if given token matches with given pattern
     *         false if given token does not match with given pattern
     */
    static bool Match(const TOKEN *tok, const char pattern[], const char *varname1[]=0, const char *varname2[]=0);

    bool isName() const;
    bool isNumber() const;
    bool isStandardType() const;
    static const TOKEN *findmatch(const TOKEN *tok, const char pattern[], const char *varname1[]=0, const char *varname2[]=0);
    static const TOKEN *findtoken(const TOKEN *tok1, const char *tokenstr[]);

    /**
     * Needle is build from multiple alternatives. If one of
     * them is equal to haystack, return value is 1. If there
     * are no matches, but one alternative to needle is empty
     * string, return value is 0. If needle was not found, return
     * value is -1.
     *
     * @param needle e.g. "one|two" or "|one|two"
     * @param haystack e.g. "one", "two" or "invalid"
     * @return 1 if needle is found from the haystack
     *         0 if needle was empty string
     *        -1 if needle was not found
     */
    static int multiCompare( const char *needle, const char *haystack );


    unsigned int linenr() const;
    void linenr( unsigned int linenr );

    unsigned int fileIndex() const;
    void fileIndex( unsigned int fileIndex );

    TOKEN *next() const;
    void next( TOKEN *next );

    unsigned int varId() const;
    void varId( unsigned int id );

private:
    std::string _str;
    char * _cstr;
    bool _isName;
    bool _isNumber;
    unsigned int _varId;
    TOKEN *_next;
    unsigned int _fileIndex;
    unsigned int _linenr;
};

#endif // TOKEN_H
