
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <ilogger.hpp>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //////////////////////////////////////////////////////////////////////////

    class ConsoleLog
    {
    public:
        virtual ~ConsoleLog() = default;

    public:
        void SetColorToDefault();
        void SetColor(const Color &color);

    public:
        void Write(const std::string &message);
        void WriteLine(const std::string &message);

        void Write(const std::string &message, const Color &color, const bool resetToDefault = false);
        void WriteLine(const std::string &message, const Color &color, const bool resetToDefault = false);
    };

    using UConsoleWrite = std::unique_ptr<ConsoleLog>;

    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
