
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <regex>
#include <variant>
#include <vector>

// #include "database/database.hpp"
// #include "db-manager/db-manager.hpp"
// #include "interface/i-table.hpp"
#include "logging/logging.hpp"
// #include "database/database.hpp"

#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Observer
{
    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////

    std::vector<std::string> Lex(const std::string &query)
    {
        // Define regular expressions for various SQL components
        std::string keywords =
            "(SELECT|INSERT|UPDATE|DELETE|FROM|INTO|SET|VALUES|WHERE)";
        std::string identifiers = "(\\w+(-\\w+)*)";
        std::string strings     = "'(.*?)'";
        std::string numbers     = "(\\d+)";
        std::string operators   = "([=<>]+)";
        std::string punctuation = "([*(),;])";

        // Combine regular expressions into a single pattern
        std::string pattern = keywords + "|" + identifiers + "|" + strings +
                              "|" + numbers + "|" + operators + "|" +
                              punctuation;

        // Use std::regex_iterator to tokenize the query
        std::regex tokenRegex(pattern, std::regex::icase);
        std::sregex_iterator iter(query.begin(), query.end(), tokenRegex);
        std::sregex_iterator end;

        // Store the tokens in a vector
        std::vector<std::string> tokens;
        for (; iter != end; ++iter)
        {
            for (size_t i = 1; i < iter->size(); ++i)
            {
                if ((*iter)[i].matched)
                {
                    tokens.push_back((*iter)[i].str());
                }
            }
        }

        // Remove semicolon if it exists
        if (!tokens.empty() && tokens.back() == ";")
        {
            tokens.pop_back();
        }

        return tokens;
    }

    int Main(const int count, char **values)
    {
        // std::string query = "SELECT * FROM table WHERE column = 'value';";
        std::string query =
            "SELECT * FROM table WHERE column = 'string value' AND "
            "another_column = 'second value';";

        std::vector<std::string> tokens = Lex(query);

        // Print the tokens
        for (const auto &token : tokens)
        {
            std::cout << token << " ";
        }
        std::cout << std::endl;

        return 0;
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Observer

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(const int argc, char **argv)
{
    int returnKey = 1;
    try
    {
        SQLEngine::Logging::Init();
        SQLEngine::Logging::Info("Program observer.");
        SQLEngine::Logging::Signal("Start Main().");
        SQLEngine::Logging::Signal(
            fmt::format("log-dir: {}", SQLEngine::Logging::GetLogPath()));
        returnKey = SQLEngine::Observer::Main(argc, argv);
        SQLEngine::Logging::Signal("Close Main().");
    }
    catch (std::exception &err)
    {
        std::cout
            << std::string(
                   "Catch exception, type is std::exception, message is ") +
                   err.what()
            << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown type exception was not handled" << std::endl;
    }
    return (returnKey);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
