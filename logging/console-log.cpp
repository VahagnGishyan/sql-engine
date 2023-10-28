
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
        std::cout << "ConsoleLog::SetColor method is not impled yet" << std::endl;
    }

    void ConsoleLog::Write(const std::string &message)
    {
        std::cout << "ConsoleLog::Write method is not impled yet" << std::endl;
    }
    void ConsoleLog::WriteLine(const std::string &message)
    {
        std::cout << "ConsoleLog::WriteLine method is not impled yet" << std::endl;
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
