
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "core.hpp"

#include <boost/filesystem.hpp>
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Utility
{
    auto GetEnvironmentValue(const std::string &name) -> const std::string
    {
        std::string value;
        if (name.size())
        {
#if defined _WIN32
            char *buf = nullptr;
            size_t sz = 0;

            if (_dupenv_s(&buf, &sz, name.c_str()) == 0 && buf != nullptr)
            {
                value = std::move(std::string(buf));
                free(buf);
            }
#else //__linux__
            const char *const envValue = std::getenv(name.c_str());
            value = (envValue == nullptr ? std::string()
                                         : std::string(envValue));
#endif
        }
        return (value);
    }

#if IS_LINUX or IS_MACOS
    static auto ExpandUser(const std::string &path) -> const std::string
    {
        // Get the user's home directory using Boost.Filesystem
        boost::filesystem::path homeDir = boost::filesystem::path(getenv("HOME"));

        // Specify a file path with a tilde (~)
        std::string filePathWithTilde = path;

        // Replace the tilde with the user's home directory
        if (filePathWithTilde[0] == '~')
        {
            filePathWithTilde.replace(0, 1, homeDir.string());
        }

        return filePathWithTilde;
    }
#endif

    auto GetDefaultDataPath() -> const std::string
    {
#if IS_WINDOWS
        return GetEnvironmentValue("APPDATA");
#elif IS_LINUX
        return ExpandUser("~");
#elif IS_MACOS
        return ExpandUser("~/Library/Application Support");
#else
#error "Unsupported OS"
#endif
    }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
