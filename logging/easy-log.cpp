
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

    EasyLog::EasyLog() : m_console{std::make_unique<ConsoleLog>()}, m_workDir{}
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

    auto EasyLog::GetMode() const -> const Mode
    {
        return m_consoleMode;
    }
    void EasyLog::SetMode(const Mode &mode)
    {
        m_consoleMode = mode;
    }

    void EasyLog::SetLogDir(const std::string &path)
    {
        m_workDir = path;
    }
    auto EasyLog::GetLogDir() const -> const std::string
    {
        return m_workDir;
    }

    //////////////////////////////////////////////////////////////////

    auto EasyLog::GetDefaultLogPath() -> const std::string
    {
        std::string path = Utility::GetDefaultDataPath();
        path = fmt::format("{}/easy-log/{}.txt", path, );
        return path;
    }

    //////////////////////////////////////////////////////////////////

    auto EasyLog::FormatMessage(const std::string &message, const Mode &mode) -> const std::string
    {
        auto strmode = Logging::ModeConvert::ModeAsString(mode);
        return fmt::format("[{}] {}", strmode, message);
    }

    void EasyLog::FileWrite(const std::string &message)
    {
        throw std::logic_error("EasyLog::FileWrite(), not-impl-yet");
    }

    void EasyLog::ConsolePrint(const std::string &message, const Color &color)
    {
        throw std::logic_error("EasyLog::FileWrite(), not-impl-yet");
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
