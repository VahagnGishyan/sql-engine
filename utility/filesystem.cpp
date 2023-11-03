

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "filesystem.hpp"
#include <fmt/core.h>
#include <filesystem>
#include <fstream>

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

    auto Utility::IsPathExists(const std::string &path) -> bool
    {
        fs::path filePath(path);
        return fs::exists(filePath);
    }

    void Utility::AssertPathExists(const std::string &path)
    {
        if (!IsPathExists(path))
        {
            throw std::invalid_argument(fmt::format("{} does not exist.", path));
        }
    }

    auto Utility::GetBaseDir(const std::string &path) -> const std::string
    {
        AssertPathExists(path);

        fs::path fullPath(path);
        // Get the parent directory path
        fs::path baseDir = fullPath.parent_path();

        // Convert the parent directory path to a string
        return baseDir.string();
    }

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

    auto Utility::IsDirExists(const std::string &path) -> bool
    {
        if (IsPathExists(path) == false)
        {
            return false;
        }
        fs::path dirPath(path);
        return fs::is_directory(dirPath);
    }

    //////////////////////////////////////////////////////////////////////

    void Utility::AssertFileExists(const std::string &path)
    {
        if (!IsFileExists(path))
        {
            throw std::invalid_argument(fmt::format("{} is not a file.", path));
        }
    }

    void Utility::AssertFileNotExists(const std::string &path)
    {
        if (IsFileExists(path))
        {
            throw std::invalid_argument(fmt::format("{} file exists.", path));
        }
    }

    void Utility::AssertDirExists(const std::string &path)
    {
        if (!IsDirExists(path))
        {
            throw std::invalid_argument(fmt::format("{} is not a directory.", path));
        }
    }

    void Utility::AssertDirNotExists(const std::string &path)
    {
        if (IsDirExists(path))
        {
            throw std::invalid_argument(fmt::format("{} directory exists.", path));
        }
    }

    //////////////////////////////////////////////////////////////////////

    auto Utility::CheckFileExtension(const std::string &path, const std::string &extension) -> bool
    {
        AssertFileExists(path);
        fs::path filePath(path);

        // Check if the path is a regular file and the extension matches
        if (filePath.has_extension())
        {
            std::string fileExtension = filePath.extension().string();
            // Convert the extension to lowercase for case-insensitive comparison
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
            std::string expectedExtension = extension;
            std::transform(expectedExtension.begin(), expectedExtension.end(), expectedExtension.begin(), ::tolower);
            return fileExtension == expectedExtension;
        }

        return false;
    }

    //////////////////////////////////////////////////////////////////////

    auto Utility::ListDir(const std::string &path) -> std::unique_ptr<std::vector<std::string>>
    {
        AssertDirExists(path);
        auto result = std::make_unique<std::vector<std::string>>();

        for (const auto &entry : fs::directory_iterator(path))
        {
            result->push_back(entry.path().string());
        }

        return result;
    }

    auto Utility::ListDirsInDir(const std::string &path) -> std::unique_ptr<std::vector<std::string>>
    {
        auto listDir = ListDir(path);
        auto result = std::make_unique<std::vector<std::string>>();

        for (auto &&entry : *listDir)
        {
            if (IsDirExists(entry))
            {
                result->push_back(std::move(entry));
            }
        }

        return result;
    }

    auto Utility::ListFilesInDir(const std::string &path) -> std::unique_ptr<std::vector<std::string>>
    {
        auto listDir = ListDir(path);
        auto result = std::make_unique<std::vector<std::string>>();

        for (auto &&entry : *listDir)
        {
            if (IsFileExists(entry))
            {
                result->push_back(std::move(entry));
            }
        }

        return result;
    }

    auto Utility::ListFilesInDir(const std::string &path, const std::string &extension) -> std::unique_ptr<std::vector<std::string>>
    {
        auto listDir = ListDir(path);
        auto result = std::make_unique<std::vector<std::string>>();

        for (auto &&entry : *listDir)
        {
            if (CheckFileExtension(entry, extension))
            {
                result->push_back(std::move(entry));
            }
        }

        return result;
    }

    //////////////////////////////////////////////////////////////////////

    auto Utility::IsDirEmpty(const std::string &path) -> bool
    {
        AssertDirExists(path);
        return fs::is_empty(path);
    }

    void Utility::AssertDirEmpty(const std::string &path)
    {
        if (!IsDirEmpty(path))
        {
            throw std::runtime_error("Directory is not empty: " + path);
        }
    }

    //////////////////////////////////////////////////////////////////////

    void Utility::MakeDir(const std::string &path, const Option::ExistOk existok,
                          const Option::CreateBaseDirectory &createbase)
    {
        if (!existok)
        {
            AssertDirNotExists(path);
        }
        else if (IsDirExists(path))
        {
            return;
        }

        auto &&base = GetBaseDir(path);
        if (!createbase)
        {
            AssertDirNotExists(base);
        }
        else if (IsDirExists(path) == false)
        {
            MakeDir(base, Option::ExistOk{false}, createbase);
        }

        if (!fs::create_directory(path))
        {
            throw std::runtime_error("Failed to create directory: " + path);
        }
    }

    void Utility::RemoveDir(const std::string &path)
    {
        AssertDirExists(path);

        try
        {
            fs::remove_all(path);
        }
        catch (const fs::filesystem_error &e)
        {
            throw std::runtime_error("Failed to remove directory: " + path);
        }
    }

    //////////////////////////////////////////////////////////////////////

    void Utility::CreateEmptyFile(const std::string &path)
    {
        AssertFileNotExists(path);
        std::ofstream file(path);
        if (!file)
        {
            throw std::runtime_error("Failed to create an empty file: " + path);
        }
    }

    void Utility::RemoveFile(const std::string &path)
    {
        AssertFileExists(path);
        try
        {
            fs::remove(path);
        }
        catch (const fs::filesystem_error &e)
        {
            throw std::runtime_error("Failed to remove file: " + path);
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
