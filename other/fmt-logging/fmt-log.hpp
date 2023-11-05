
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "ilogger.hpp"
#include <fstream>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class FMTLogger : public ILogger
    {
    protected:
        Mode m_consoleMode;
        std::ofstream m_logfile;

    public:
        FMTLogger();

    public:
        void Message(const std::string &message) override;
        void Info(const std::string &message) override;
        void Signal(const std::string &message) override;
        void Warning(const std::string &message) override;
        void Debug(const std::string &message) override;
        void Error(const std::string &message, const bool dothrow) override;

    public:
        auto GetMode() const -> const Mode override;
        void SetMode(const Mode &mode) override;

    public:
        auto GetLogPath() -> const std::string override;
        virtual auto GetLogFileName() -> const std::string;

    public:
        static auto GetDefaultLogPath() -> const std::string;

    protected:
        void DoLog(const std::string &message, const Mode &mode, const Color &color = Color::Default);
        auto PrepareMessage(const std::string &message, const Mode &mode) -> const std::string;
        void WriteInFile(const std::string &message, const Mode &mode);
        void PrintInConsole(const std::string &message, const Mode &mode, const Color &color);
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
