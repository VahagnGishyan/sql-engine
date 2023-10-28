
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "ilogger.hpp"
#include "console-log.hpp"
#include "file-log.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    class EasyLog : public ILogger
    {
    protected:
        Mode m_consoleMode;
        UConsoleWrite m_console;
        UFileLog m_file;

    public:
        EasyLog();

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
        virtual auto GetLogPath() -> const std::string override;

        //////////////////////////////////////////////////////////////////

    public:
        static auto GetDefaultLogPath() -> const std::string;

    protected:
        auto FormatMessage(const std::string &message, const Mode &mode) -> const std::string;
        void FileWrite(const std::string &message);
        void ConsolePrint(const std::string &message, const Mode &mode, const Color &color);
        void LogMessage(const std::string &message, const Mode &mode, const Color &color = Color::Default);
    };
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
