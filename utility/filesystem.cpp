

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "filesystem.hpp"

#include <fmt/core.h>

#include <filesystem>
#include <fstream>

// #include <iostream>

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
            throw std::invalid_argument(
                fmt::format("{} does not exist.", path));
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
            throw std::invalid_argument(
                fmt::format("{} is not a directory.", path));
        }
    }

    void Utility::AssertDirNotExists(const std::string &path)
    {
        if (IsDirExists(path))
        {
            throw std::invalid_argument(
                fmt::format("{} directory exists.", path));
        }
    }

    //////////////////////////////////////////////////////////////////////

    auto Utility::CheckFileExtension(const std::string &path,
                                     const std::string &extension) -> bool
    {
        AssertFileExists(path);
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

    //////////////////////////////////////////////////////////////////////

    auto Utility::ListDir(const std::string &path,
                          const Option::FullPaths returnFullPaths)
        -> std::unique_ptr<std::vector<std::string>>
    {
        AssertDirExists(path);
        auto result = std::make_unique<std::vector<std::string>>();

        for (const auto &entry : fs::directory_iterator(path))
        {
            if (returnFullPaths)
            {
                result->push_back(entry.path().string());
            }
            else
            {
                result->push_back(entry.path().filename().string());
            }
        }

        return result;
    }

    auto Utility::ListDirsInDir(const std::string &path,
                                const Option::FullPaths returnFullPaths)
        -> std::unique_ptr<std::vector<std::string>>
    {
        auto listDir = ListDir(path, returnFullPaths);
        auto result  = std::make_unique<std::vector<std::string>>();

        for (auto &&entry : *listDir)
        {
            std::string entrypath = "";
            if (returnFullPaths == false)
            {
                entrypath = path + '/';
            }
            entrypath += entry;
            if (IsDirExists(entrypath))
            {
                result->push_back(std::move(entry));
            }
        }

        return result;
    }

    auto Utility::ListFilesInDir(const std::string &path,
                                 const Option::FullPaths returnFullPaths)
        -> std::unique_ptr<std::vector<std::string>>
    {
        auto listDir = ListDir(path, returnFullPaths);
        auto result  = std::make_unique<std::vector<std::string>>();

        // std::cout << "point-input, size: " << listDir->size() << std::endl;

        for (auto &&entry : *listDir)
        {
            // std::cout << "point-entry, entry: " << entry << " exists: ";
            std::string entrypath = "";
            if (returnFullPaths == false)
            {
                entrypath = path + '/';
            }
            entrypath += entry;
            if (IsFileExists(entrypath))
            {
                // std::cout << "true" << std::endl;
                result->push_back(std::move(entry));
                continue;
            }
            // std::cout << "false" << std::endl;
        }

        // std::cout << "point-output, size: " << result->size() << std::endl;

        return result;
    }

    auto Utility::ListFilesInDir(const std::string &path,
                                 const std::string &extension,
                                 const Option::FullPaths returnFullPaths)
        -> std::unique_ptr<std::vector<std::string>>
    {
        auto listDir = ListDir(path, returnFullPaths);
        auto result  = std::make_unique<std::vector<std::string>>();

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

    void Utility::MakeDir(const std::string &path,
                          const Option::ExistOk existok,
                          const Option::CreateBaseDirectory &createbase)
    {
        // std::cout << "point-start" << std::endl;
        if (!existok)
        {
            AssertDirNotExists(path);
        }
        else if (IsDirExists(path))
        {
            return;
        }

        // std::cout << "point-existok-end" << std::endl;

        auto &&base = GetBaseDir(path);
        // std::cout << "point-base-is:" << base << std::endl;
        if (!createbase)
        {
            AssertDirExists(base);
        }
        else if (IsDirExists(base) == false)
        {
            MakeDir(base, Option::ExistOk{false}, createbase);
        }

        // std::cout << "point-createbase-end" << std::endl;

        if (!fs::create_directory(path))
        {
            throw std::runtime_error("Failed to create directory: " + path);
        }

        // std::cout << "point-exit" << std::endl;
    }

    void Utility::RemoveDir(const std::string &path,
                            const Option::MustExist mustexist)
    {
        if (mustexist)
        {
            AssertDirExists(path);
        }
        else if (IsDirExists(path) == false)
        {
            auto &&base = GetBaseDir(path);
            AssertDirExists(base);
            return;
        }

        try
        {
            fs::remove_all(path);
        }
        catch (const fs::filesystem_error &exception)
        {
            throw std::runtime_error("Failed to remove directory: " + path +
                                     ", what: " + exception.what());
        }
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
