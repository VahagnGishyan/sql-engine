

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <filesystem>
#include <fstream>

#include "core.hpp"
#include "filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    namespace fs = std::filesystem;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////

    auto Utility::IsFileExists(const std::string &path) -> bool
    {
        if (IsPathExists(path) == false)
        {
            return false;
        }
        fs::path filePath(path);
        return fs::is_regular_file(filePath);
    }

    //////////////////////////////////////////////////////////////////////

    void Utility::AssertFileExists(const std::string &path)
    {
        Assert(IsFileExists(path), fmt::format("{} is not a file.", path));
    }

    void Utility::AssertFileNotExists(const std::string &path)
    {
        Assert(!IsFileExists(path), fmt::format("{} file exists.", path));
    }

    //////////////////////////////////////////////////////////////////////

    auto Utility::CheckFileExtension(const std::string &path,
                                     const std::string &extension) -> bool
    {
        fs::path filePath(path);

        // Check if the path is a regular file and the extension matches
        if (filePath.has_extension())
        {
            std::string fileExtension = filePath.extension().string();
            // Ensure the expected extension has a leading dot
            std::string expectedExtension = extension;
            if (expectedExtension.front() != '.')
            {
                expectedExtension = "." + expectedExtension;
            }
            // Convert both extensions to lowercase for case-insensitive
            // comparison
            std::transform(fileExtension.begin(), fileExtension.end(),
                           fileExtension.begin(), ::tolower);
            std::transform(expectedExtension.begin(), expectedExtension.end(),
                           expectedExtension.begin(), ::tolower);
            return fileExtension == expectedExtension;
        }

        return false;
    }

    void Utility::AssertFileExtension(const std::string &path,
                                      const std::string &extension)
    {
        Assert(CheckFileExtension(path, extension),
               fmt::format("file: {} does not have the specified extension: {}",
                           path, extension));
    }

    //////////////////////////////////////////////////////////////////////

    void Utility::MakeEmptyFile(const std::string &path,
                                const Option::ExistOk existok,
                                const Option::CreateBaseDirectory &createbase)
    {
        if (!existok)
        {
            AssertFileNotExists(path);
        }
        else if (IsFileExists(path))
        {
            return;
        }

        if (createbase)
        {
            auto &&base = GetBaseDir(path);
            MakeDir(base, Option::ExistOk{true}, createbase);
        }

        std::ofstream file(path);
        if (!file)
        {
            throw std::runtime_error("Failed to create an empty file: " + path);
        }
    }

    void Utility::RemoveFile(const std::string &path,
                             const Option::MustExist mustexist)
    {
        if (mustexist)
        {
            AssertFileExists(path);
        }
        else if (IsFileExists(path) == false)
        {
            auto &&base = GetBaseDir(path);
            AssertDirExists(base);
            return;
        }

        try
        {
            fs::remove(path);
        }
        catch (const fs::filesystem_error &exception)
        {
            throw std::runtime_error("Failed to remove file: " + path +
                                     ", what: " + exception.what());
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
