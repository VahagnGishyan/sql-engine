
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
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
        Default = Signal,
        Debug,
        Warning,
        Error,
    };

    namespace ModeConvert
    {
        auto GetModeStrList()
            -> const std::vector<std::pair<Mode, std::string>> &;
        auto ModeAsString(const Mode &mode) -> const std::string;
        auto StringAsMode(const std::string strmode) -> const Mode;
    }  // namespace ModeConvert

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
        auto GetColorStrList()
            -> const std::vector<std::pair<Color, std::string>> &;
        auto ColorAsString(const Color &color) -> const std::string;
        auto StringAsColor(const std::string strclr) -> const Color;
    }  // namespace ColorConvert
}  // namespace SQLEngine::Logging

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
