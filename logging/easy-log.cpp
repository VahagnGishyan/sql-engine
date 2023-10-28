
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include "easy-log.hpp"
#include "utility.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// def PrintInfo(message):
//     print(GREEN + message + RESET)

// def PrintSignal(message):
//     print(GREEN + message + RESET)

// def PrintWarning(message):
//     print(YELLOW + message + RESET)

// def PrintDebug(message):
//     print(BLUE + message + RESET)

// def PrintError(message):
//     print(RED + message + RESET)

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    EasyLog::EasyLog() : m_console{std::make_unique<ConsoleLog>()},
                         m_file{std::move(GetEasyFileLog())} m_consoleMode{Mode::Default}
    {
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void EasyLog::Message(const std::string &message)
    {
        LogMessage(message, Mode::Message, Color::Default);
    }
    void EasyLog::Info(const std::string &message)
    {
        EasyLog::LogMessage(message, Mode::Info, Color::Default);
    }
    void EasyLog::Signal(const std::string &message)
    {
        LogMessage(message, Mode::Signal, Color::Green);
    }
    void EasyLog::Warning(const std::string &message)
    {
        LogMessage(message, Mode::Message, Color::Yellow);
    }
    void EasyLog::Debug(const std::string &message)
    {
        LogMessage(message, Mode::Debug, Color::Blue);
    }
    void EasyLog::Error(const std::string &message, const bool dothrow)
    {
        LogMessage(message, Mode::Error, Color::Red);
    }

    //////////////////////////////////////////////////////////////////////

    auto EasyLog::GetMode() const -> const Mode
    {
        return m_consoleMode;
    }
    void EasyLog::SetMode(const Mode &mode)
    {
        m_consoleMode = mode;
    }

    //////////////////////////////////////////////////////////////////////

    auto EasyLog::GetDefaultLogPath() -> const std::string
    {
        return FileLog::GetDefaultLogPath();
    }

    //////////////////////////////////////////////////////////////////

    auto EasyLog::FormatMessage(const std::string &message, const Mode &mode) -> const std::string
    {
        auto strmode = Logging::ModeConvert::ModeAsString(mode);
        return fmt::format("[{}] {}", strmode, message);
    }

    void EasyLog::FileWrite(const std::string &message)
    {
        m_file->WriteLine(message);
    }

    void EasyLog::ConsolePrint(const std::string &message, const Mode &mode, const Color &color)
    {
        if (GetMode() <= mode)
        {
            m_console->WriteLine(message, color, true);
        }
    }

    void EasyLog::LogMessage(const std::string &message, const Mode &mode, const Color &color)
    {
        auto formatedMsg = FormatMessage(message, mode);
        ConsolePrint(formatedMsg, color);
        FileWrite(formatedMsg);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
