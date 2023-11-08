
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "fmt-log.hpp"

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iterator>
#include <optional>
#include <stdexcept>

#include "app-info/application.hpp"
#include "logging/logging.hpp"
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

    FMTLogger::FMTLogger() :
        m_logfile{}, m_consoleMode{Mode::Default}, m_enableBuffering{true}
    {
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void FMTLogger::Init()
    // void FMTLogger::Init(const std::string &logdir)
    {
        auto &&logfilepath = GetLogPath();
        PrepareLogDir(Utility::GetBaseDir(logfilepath));
        m_logfile.open(logfilepath);
        if (!m_logfile)
        {
            throw std::runtime_error{
                fmt::format("Enable to open file: {}", logfilepath)};
        }
    }

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
        return fmt::format("{}-{:%Y-%m-%d-%Hh-%Mm}.log", appname, timenow);
    }

    void FMTLogger::PrepareLogDir(const std::string &logdir)
    {
        // Logging::Debug(
        //     fmt::format("FMTLogger::PrepareLogDir(path: {})", logdir));
        Utility::MakeDir(logdir, Utility::Option::ExistOk{true},
                         Utility::Option::CreateBaseDirectory{true});
        auto &&logfiles = Utility::ListFilesInDir(
            logdir, ".log", Utility::Option::FullPaths{false});

        // Logging::Debug(
        //     fmt::format("logfiles.size: {}\n"
        //                 "log-dir: {}\n"
        //                 "elements: {}",
        //                 logfiles->size(), logdir, *logfiles));

        auto resolutionNumber = ResolutionNumberOfLogFiles();
        if (resolutionNumber == 1)
        {
            Logging::Error("FMTLogger, ResolutionNumberOfLogFiles must be > 1.",
                           /*dothrow = */ true);
        }
        if (logfiles->size() >= (resolutionNumber - 1))
        {
            std::sort(logfiles->begin(), logfiles->end(), std::greater<>());
            auto iter = logfiles->begin();
            std::advance(iter, resolutionNumber - 1);
            std::for_each(iter, logfiles->end(),
                          [&logdir](const std::string &path)
                          {
                              Utility::RemoveFile(logdir + '/' + path);
                          });
        }
    }

    auto FMTLogger::ResolutionNumberOfLogFiles() const -> int
    {
        return (10);
    }
    //////////////////////////////////////////////////////////////////////

    void FMTLogger::EnableBuffering(const bool order)
    {
        m_enableBuffering = order;
    }

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

    auto FMTLogger::GetDefaultLogPath() -> const std::string
    {
        std::string path = Utility::GetDefaultDataPath();
        auto &&info      = Application::GetInfo();
        auto &&appname   = info.GetName();
        path             = fmt::format("{}/{}/logs", path, appname);
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
        if (m_logfile.is_open() == false)
        {
            return;
        }

        time_point<system_clock> timenow = system_clock::now();
        auto strmode = Logging::ModeConvert::ModeAsString(mode);
        auto &&formatedMsg =
            fmt::format("[{:%H:%M:%S}] {:<7} :: {}", timenow, strmode, message);
        m_logfile << formatedMsg << std::endl;
        if (m_enableBuffering == false)
        {
            m_logfile.flush();
        }
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
