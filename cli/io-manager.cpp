
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "cli-app-manager.hpp"

// #include <fmt/core.h>
#include <iostream>
#include <sstream>

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
        std::cout << prompt << ": ";
        std::vector<std::string> tokens;

        std::string word;
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
    void IOManager::Print(const std::string& prompt) const
    {
        std::cout << prompt;
    }
    void IOManager::PrintLine(const std::string& prompt) const
    {
        std::cout << prompt << std::endl;
    }

    void IOManager::PrintMessage(const std::vector<std::string>& content) const
    {
        for (auto&& line : content)
        {
            PrintLine(line);
        }
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
