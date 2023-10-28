
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "ilogger.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    class EasyLog : public ILogger
    {
    protected:
        Mode m_consoleMode;
        std::string m_workDir;

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
        void SetLogDir(const std::string &path) override;
        auto GetLogDir() const -> const std::string override;

        //////////////////////////////////////////////////////////////////

    protected:
        auto FileWrite(const std::string &message, const Mode &mode);
        void ConsolePrint(const std::string &message, const Color &color);
        void LogMessage(const std::string &message, const Mode &mode, const Color &color = Color::Default);
    };
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
