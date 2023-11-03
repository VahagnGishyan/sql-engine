
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "core.hpp"
#include <filesystem>
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
#if defined IS_WINDOWS
            char *buf = nullptr;
            size_t sz = 0;

            if (_dupenv_s(&buf, &sz, name.c_str()) == 0 && buf != nullptr)
            {
                value = std::move(std::string(buf));
                free(buf);
            }
#elif defined(IS_LINUX) or defined(IS_MACOS) 
            const char *const envValue = std::getenv(name.c_str());
            value = (envValue == nullptr ? std::string()
                                         : std::string(envValue));
#else
#error "Unsupported OS"
#endif
        }
        return (value);
    }

#if defined(IS_LINUX) or defined(IS_MACOS) 
    static auto ExpandUser(const std::string &path) -> const std::string
    {
        // Get the user's home directory using std.Filesystem
        std::filesystem::path homeDir = std::filesystem::path(getenv("HOME"));

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
#if defined IS_WINDOWS
        return GetEnvironmentValue("APPDATA");
#elif defined IS_LINUX
        return ExpandUser("~");
#elif defined IS_MACOS
        return ExpandUser("~/Library/Application Support");
#else
    #error "Unsupported OS"
#endif
    }
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
