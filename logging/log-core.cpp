
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "log-core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    namespace ModeConvert
    {
        auto GetModeStrList() -> const std::vector<std::pair<Mode, std::string>> &
        {
            static std::vector<std::pair<Mode, std::string>> list{
                {Mode::Message, "Message"},
                {Mode::Info, "Info"},
                {Mode::Signal, "Signal"},
                {Mode::Warning, "Warning"},
                {Mode::Debug, "Debug"},
                {Mode::Error, "Error"}};
            return list;
        }

        auto ModeAsString(const Mode &mode) -> const std::string
        {
            auto &&list = GetModeStrList();
            auto end = list.end();
            auto itr = std::find_if(list.begin(), end,
                                    [&mode](const std::pair<Mode, std::string> &element)
                                    {
                                        return (element.first == mode);
                                    });
            if (itr == end)
            {
                throw std::invalid_argument("ModeAsString(Mode mode), mode is invalid");
            }
            return (itr->second);
        }

        auto StringAsMode(const std::string strmode) -> const Mode
        {
            auto &&list = GetModeStrList();
            auto end = list.end();
            auto itr =
                std::find_if(list.begin(), end,
                             [&strmode](const std::pair<Mode, std::string> &element)
                             {
                                 return (element.second == strmode);
                             });
            if (itr == end)
            {
                throw std::invalid_argument("StringAsMode(string mode), mode is invalid");
            }
            return (itr->first);
        }
    };

    namespace ColorConvert
    {
        auto GetColorStrList() -> const std::vector<std::pair<Color, std::string>> &
        {
            static std::vector<std::pair<Color, std::string>> list{
                {Color::Unset, "Unset"},
                {Color::Default, "Default"},
                {Color::Green, "Green"},
                {Color::Yellow, "Yellow"},
                {Color::Blue, "Blue"},
                {Color::Red, "Red"},
            };
            return list;
        }
        auto ColorAsString(const Color &color) -> const std::string
        {
            auto &&list = GetColorStrList();
            auto end = list.end();
            auto itr = std::find_if(list.begin(), end,
                                    [&color](const std::pair<Color, std::string> &element)
                                    {
                                        return (element.first == color);
                                    });
            if (itr == end)
            {
                throw std::invalid_argument("ColorAsString(Color color), color is invalid");
            }
            return (itr->second);
        }
        auto StringAsColor(const std::string strclr) -> const Color
        {
            auto &&list = GetColorStrList();
            auto end = list.end();
            auto itr =
                std::find_if(list.begin(), end,
                             [&strclr](const std::pair<Color, std::string> &element)
                             {
                                 return (element.second == strclr);
                             });
            if (itr == end)
            {
                throw std::invalid_argument("StringAsColor(string strclr), strclr is invalid");
            }
            return (itr->first);
        }
    };
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
