
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <map>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#ifdef yyFlexLexer
#define YY_FLEX_LEXER
#define YY_NO_UNISTD_H
#endif  // yyFlexLexer

#ifndef YY_FLEX_LEXER
#include "FlexLexer.h"
#endif  // YY_FLEX_LEXER

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// namespace SQLEngine::QueryParser
// {
//////////////////////////////////////////////////////////////////////
//                                                                  //
//////////////////////////////////////////////////////////////////////

class SQLQueryLexer : public yyFlexLexer
{
   protected:
    std::string m_currentLexem;
    std::string m_currentValue;
    // temp
    std::ostream& out;

   protected:
    int ProcessDigit(); /* 0123456789 */
    int ProcessAlpha(); /* Digit,
                           abcdefghijklmnopqrstuvwxyz,
                           ABCDEFGHIJKLMNOPQRSTUVWXYZ,
                           _ and - */

   protected:
    int ProcessInsertInto();

   protected:
    int ProcessUnknown();

   public:
    SQLQueryLexer(std::istream& in, std::ostream& out) :
        yyFlexLexer(&in, &out), out{out}
    {
    }

   public:
    void PrintCurrent() const;
    int yylex() override;
}

//////////////////////////////////////////////////////////////////////
//                                                                  //
//////////////////////////////////////////////////////////////////////
// }  // namespace SQLEngine::QueryParser

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
