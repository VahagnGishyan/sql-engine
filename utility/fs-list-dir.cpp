

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <filesystem>
#include <fstream>

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
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
