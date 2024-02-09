
#include "lexer.hpp"

// int SQLQueryLexer::yylex()
// {
//     return 1;
// }

// int USharpLexer::Lexer::yylex()
//{
//	return (1);
// }

int main()
{
    auto lexer = std::make_unique<SQLQueryLexer>();
    while (lexer->yylex() != 0)
    {
        lexer->PrintCurrent();
    }
}