
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "console-log.hpp"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void ConsoleLog::SetColorToDefault()
    {
        SetColor(Color::Default);
    }

    void ConsoleLog::SetColor(const Color &color)
    {
        // temp
        // std::cout << "ConsoleLog::SetColor method is not impled yet" << std::endl;
    }

    void ConsoleLog::Write(const std::string &message)
    {
        std::cout << message;
    }
    void ConsoleLog::WriteLine(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    void ConsoleLog::Write(const std::string &message, const Color &color, const bool resetToDefault)
    {
        if (color != Color::Unset)
        {
            SetColor(color);
        }

        Write(message);

        if (resetToDefault)
        {
            SetColorToDefault();
        }
    }

    void ConsoleLog::WriteLine(const std::string &message, const Color &color, const bool resetToDefault)
    {
        if (color != Color::Unset)
        {
            SetColor(color);
        }

        WriteLine(message);

        if (resetToDefault)
        {
            SetColorToDefault();
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
