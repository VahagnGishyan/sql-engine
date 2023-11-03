
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include "boost-wrapper.hpp"
#include "utility/core.hpp"

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

    BoostLogWrapper::BoostLogWrapper() : m_console{std::make_unique<ConsoleLog>()},
                                         m_file{std::move(GetEasyFileLog())},
                                         m_consoleMode{Mode::Default}
    {
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void BoostLogWrapper::Message(const std::string &message)
    {
        LogMessage(message, Mode::Message, Color::Default);
    }
    void BoostLogWrapper::Info(const std::string &message)
    {
        BoostLogWrapper::LogMessage(message, Mode::Info, Color::Default);
    }
    void BoostLogWrapper::Signal(const std::string &message)
    {
        LogMessage(message, Mode::Signal, Color::Green);
    }
    void BoostLogWrapper::Warning(const std::string &message)
    {
        LogMessage(message, Mode::Message, Color::Yellow);
    }
    void BoostLogWrapper::Debug(const std::string &message)
    {
        LogMessage(message, Mode::Debug, Color::Blue);
    }
    void BoostLogWrapper::Error(const std::string &message, const bool dothrow)
    {
        LogMessage(message, Mode::Error, Color::Red);
    }

    //////////////////////////////////////////////////////////////////////

    auto BoostLogWrapper::GetMode() const -> const Mode
    {
        return m_consoleMode;
    }
    void BoostLogWrapper::SetMode(const Mode &mode)
    {
        m_consoleMode = mode;
    }

    //////////////////////////////////////////////////////////////////////

    auto BoostLogWrapper::GetLogPath() -> const std::string
    {
        return (FileLog::GetDefaultLogPath());
    }

    //////////////////////////////////////////////////////////////////////

    auto BoostLogWrapper::GetDefaultLogPath() -> const std::string
    {
        return FileLog::GetDefaultLogPath();
    }

    //////////////////////////////////////////////////////////////////

    auto BoostLogWrapper::FormatMessage(const std::string &message, const Mode &mode) -> const std::string
    {
        auto strmode = Logging::ModeConvert::ModeAsString(mode);
        return fmt::format("[{}] {}", strmode, message);
    }

    void BoostLogWrapper::FileWrite(const std::string &message)
    {
        m_file->WriteLine(message);
    }

    void BoostLogWrapper::ConsolePrint(const std::string &message, const Mode &mode, const Color &color)
    {
        if (GetMode() <= mode)
        {
            m_console->WriteLine(message, color, true);
        }
    }

    void BoostLogWrapper::LogMessage(const std::string &message, const Mode &mode, const Color &color)
    {
        auto formatedMsg = FormatMessage(message, mode);
        ConsolePrint(formatedMsg, mode, color);
        FileWrite(formatedMsg);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
