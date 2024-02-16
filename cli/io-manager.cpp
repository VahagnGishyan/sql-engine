
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/color.h>
#include <fmt/ranges.h>

#include <iostream>
#include <sstream>

#include "cli-app-manager.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::CLI
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto IOManager::ReadUserInput(const std::string& prompt) const
        -> const std::vector<std::string>
    {
        if (prompt.size())
        {
            fmt::print(fg(fmt::color::green), "{}: ", prompt);
            // fmt::print(fg(fmt::color::blue), "{}: ", prompt);
            // fmt::print(fg(fmt::color::purple), "{}: ", prompt);
        }
        std::vector<std::string> tokens;

        std::string word           = "--";
        char symbol                = '\0';
        constexpr char enterSymbol = '\n';
        while (symbol = std::cin.get())
        {
            if (std::isspace(symbol))
            {
                if (word.size())
                {
                    tokens.emplace_back(std::move(word));
                }
                if (symbol == enterSymbol)
                {
                    break;
                }
                continue;
            }
            word.push_back(symbol);
        }

        return tokens;
    }
    void IOManager::Print(const std::string& message) const
    {
        fmt::print(fg(fmt::color::yellow), message);
    }
    void IOManager::PrintLine(const std::string& message) const
    {
        fmt::print(fg(fmt::color::yellow), "{}\n", message);
    }

    void IOManager::PrintMessage(const std::vector<std::string>& content) const
    {
        for (auto&& line : content)
        {
            PrintLine(line);
        }
    }
    void IOManager::PrintError(const std::string& message) const
    {
        fmt::print(fg(fmt::color::red), "{}\n", message);
    }

    auto IOManager::IsEnd(const std::vector<std::string>& input) const -> bool
    {
        if (input.size() == 1)
        {
            return input[0] == GetEndValue();
        }
        return false;
    }
    auto IOManager::GetEndValue() const -> const std::string
    {
        return m_endValue;
    }
    auto IOManager::SetEndValue(const std::string& value)
    {
        m_endValue = value;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::CLI

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
