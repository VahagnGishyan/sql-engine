%option yyclass="SQLQueryLexer"
%option c++

%{

#include "query-parser/lexer.hpp"

%}

WS      [ \t\n\v]+
ALPHA	[A-Za-z]
DIGIT   [0-9]
DIGIT1  [1-9]

%%

{WS}				/* skip blanks and tabs */

"insert-into"		return ProcessInsertInto();

{DIGIT1}{DIGIT}*				return ProcessDigit();
(({ALPHA}+)|({DIGIT}+)|[_-])*	return ProcessAlpha();

.								return ProcessUnknown();

%%

// nothing