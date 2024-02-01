

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <filesystem>
#include <fstream>

#include "core.hpp"
#include "filesystem.hpp"

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

    auto Utility::IsDirExists(const std::string &path) -> bool
    {
        if (IsPathExists(path) == false)
        {
            return false;
        }
        fs::path dirPath(path);
        return fs::is_directory(dirPath);
    }

    auto Utility::GetBaseDir(const std::string &path,
                             const Option::MustExist &mustexist)
        -> const std::string
    {
        auto strpath = path;
        if (path.empty())
        {
            // Handle the case of an empty path
            throw std::invalid_argument("Empty path provided");
        }
        if ((strpath.back() == '\\') || (strpath.back() == '/'))
        {
            strpath.pop_back();
        }

        fs::path fullPath(strpath);
        fs::path baseDir = fullPath.parent_path();

        if (baseDir.empty() && mustexist)
        {
            // Handle the case of the root directory
            throw std::invalid_argument("Path is already the root directory");
        }

        return baseDir.string();
    }

    auto Utility::ExtractFileName(const std::string &path,
                                  const Option::MustExist &mustexist)
        -> const std::string
    {
        if (mustexist == true)
        {
            Utility::AssertDirExists(path);
        }

        std::filesystem::path fspath(path);
        return fspath.filename().string();
    }

    //////////////////////////////////////////////////////////////////////

    void Utility::AssertDirExists(const std::string &path)
    {
        Assert(IsDirExists(path), fmt::format("{} is not a directory.", path));
    }

    void Utility::AssertDirNotExists(const std::string &path)
    {
        Assert(!IsDirExists(path), fmt::format("{} directory exists.", path));
    }

    //////////////////////////////////////////////////////////////////////

    auto Utility::IsDirEmpty(const std::string &path) -> bool
    {
        AssertDirExists(path);
        return fs::is_empty(path);
    }

    void Utility::AssertDirEmpty(const std::string &path)
    {
        Assert(IsDirEmpty(path), "Directory is not empty: " + path);
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

    /* *
     * temp
     * untested function ClearDirectoryContent
     */
    void Utility::ClearDirectoryContent(const std::string &path)
    {
        AssertDirExists(path);
        RemoveDir(path);
        MakeDir(path);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
