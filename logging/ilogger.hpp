
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>
#include <memory>
#include <vector>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    enum class Mode
    {
        Message,
        Info,
        Signal,
        Warning,
        Debug,
        Error,
    };

    namespace ModeConvert
    {
        auto GetModeStrList() -> const std::vector<std::pair<Mode, std::string>> &;
        auto ModeAsString(const Mode &mode) -> const std::string;
        auto StringAsMode(const std::string strmode) -> const Mode;
    };

    enum class Color
    {
        Unset,
        Default,
        Green,
        Yellow,
        Blue,
        Red
    };

    namespace ColorConvert
    {
        auto GetColorStrList() -> const std::vector<std::pair<Color, std::string>> &;
        auto ColorAsString(const Color &color) -> const std::string;
        auto StringAsColor(const std::string strclr) -> const Color;
    };

    class ILogger
    {
    public:
        virtual ~ILogger() = default;

    public:
        virtual void Message(const std::string &message) = 0;
        virtual void Info(const std::string &message) = 0;
        virtual void Signal(const std::string &message) = 0;
        virtual void Warning(const std::string &message) = 0;
        virtual void Debug(const std::string &message) = 0;
        virtual void Error(const std::string &message, const bool dothrow) = 0;

    public:
        virtual auto GetMode() const -> const Mode = 0;
        virtual void SetMode(const Mode &) = 0;

    public:
        virtual void SetLogDir(const std::string &path) = 0;
        virtual auto GetLogDir() const -> const std::string = 0;
    };

    using ULogger = std::unique_ptr<ILogger>;
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
