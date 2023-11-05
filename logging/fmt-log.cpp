
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "fmt-log.hpp"

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

#include <optional>
#include <stdexcept>

#include "app-info/application.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    FMTLogger::FMTLogger() : m_logfile{}, m_consoleMode{Mode::Default}
    {
        m_logfile.open(GetLogPath());
        if (!m_logfile)
        {
            throw std::runtime_error{
                fmt::format("Enable to open file: {}", GetLogPath())};
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void FMTLogger::Message(const std::string &message)
    {
        DoLog(message, Mode::Message, Color::Default);
    }
    void FMTLogger::Info(const std::string &message)
    {
        FMTLogger::DoLog(message, Mode::Info, Color::Default);
    }
    void FMTLogger::Signal(const std::string &message)
    {
        DoLog(message, Mode::Signal, Color::Green);
    }
    void FMTLogger::Debug(const std::string &message)
    {
        DoLog(message, Mode::Debug, Color::Blue);
    }
    void FMTLogger::Warning(const std::string &message)
    {
        DoLog(message, Mode::Warning, Color::Yellow);
    }
    void FMTLogger::Error(const std::string &message, const bool dothrow)
    {
        DoLog(message, Mode::Error, Color::Red);
        if (dothrow)
        {
            throw std::runtime_error{message};
        }
    }

    //////////////////////////////////////////////////////////////////////

    auto FMTLogger::GetMode() const -> const Mode
    {
        return m_consoleMode;
    }
    void FMTLogger::SetMode(const Mode &mode)
    {
        m_consoleMode = mode;
    }

    //////////////////////////////////////////////////////////////////////

    auto FMTLogger::GetLogPath() -> const std::string
    {
        std::string path = FMTLogger::GetDefaultLogPath();
        std::string name = GetLogFileName();
        path             = fmt::format("{}/{}", path, name);
        return path;
    }

    auto FMTLogger::GetLogFileName() -> const std::string
    {
        auto &&info    = Application::GetInfo();
        auto &&appname = info.GetName();
        using std::chrono::system_clock;
        using std::chrono::time_point;
        time_point<system_clock> timenow = system_clock::now();
        return fmt::format("log-{}-{:%Y-%m-%d}.txt", appname, timenow);
    }

    //////////////////////////////////////////////////////////////////////

    auto FMTLogger::GetDefaultLogPath() -> const std::string
    {
        std::string path = Utility::GetDefaultDataPath();
        auto &&info      = Application::GetInfo();
        auto &&appname   = info.GetName();
        path             = fmt::format("{}/{}/logs", path, appname);
        Utility::MakeDir(path, Utility::Option::ExistOk{true},
                         Utility::Option::CreateBaseDirectory{true});
        return path;
    }

    //////////////////////////////////////////////////////////////////

    void FMTLogger::DoLog(const std::string &message, const Mode &mode,
                          const Color &color)
    {
        auto formatedMsg = PrepareMessage(message, mode);
        WriteInFile(formatedMsg, mode);
        PrintInConsole(formatedMsg, mode, color);
    }

    auto FMTLogger::PrepareMessage(const std::string &message, const Mode &mode)
        -> const std::string
    {
        return message;
    }

    void FMTLogger::WriteInFile(const std::string &message, const Mode &mode)
    {
        using std::chrono::system_clock;
        using std::chrono::time_point;
        time_point<system_clock> timenow = system_clock::now();
        auto strmode = Logging::ModeConvert::ModeAsString(mode);
        auto &&formatedMsg =
            fmt::format("[{:%H:%M:%S}] {:<7} :: {}", timenow, strmode, message);
        m_logfile << formatedMsg << std::endl;
    }

    //////////////////////////////////////////////////////////////////////

    auto ColorToFMTColor(const Color &color) -> fmt::color
    {
        switch (color)
        {
            case Color::Blue:
                return fmt::color::blue;
            case Color::Green:
                return fmt::color::green;
            case Color::Red:
                return fmt::color::red;
            case Color::Yellow:
                return fmt::color::yellow;

            case Color::Unset:
                throw std::invalid_argument{"ColorToFMTColor: color = unset"};
            case Color::Default:
            default:
                throw std::invalid_argument{
                    "ColorToFMTColor: case default, invalid or unsupported "
                    "color."};
        }
    }

    auto GetFMTTextStyle(const Mode &mode, const Color &color)
        -> std::optional<fmt::v10::text_style>
    {
        switch (mode)
        {
            case Mode::Info:
            case Mode::Message:
                return std::nullopt;
            case Mode::Signal:
            {
                auto &&fmtcolor = ColorToFMTColor(color);
                return fmt::fg(fmtcolor);
            }
            case Mode::Debug:
            {
                auto &&fmtcolor = ColorToFMTColor(color);
                return fmt::fg(fmtcolor);
            }
            case Mode::Warning:
            {
                auto &&fmtcolor = ColorToFMTColor(color);
                return fmt::fg(fmtcolor) | fmt::emphasis::italic;
            }
            case Mode::Error:
            {
                auto &&fmtcolor = ColorToFMTColor(color);
                return fmt::fg(fmtcolor) | fmt::emphasis::bold;
            }

            default:
                throw std::invalid_argument{
                    "GetFMTTextStyle: case default, invalid or unsupported "
                    "mode."};
        }
    }

    void FMTLogger::PrintInConsole(const std::string &message, const Mode &mode,
                                   const Color &color)
    {
        if (GetMode() <= mode)
        {
            auto &&textstyle = GetFMTTextStyle(mode, color);
            if (textstyle)
            {
                fmt::print(*textstyle, "{}\n", message);
                return;
            }
            fmt::print("{}\n", message);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Logging

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////