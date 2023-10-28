

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "defines.hpp"
#include <memory>
#include <vector>
#include <string>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Utility
{
    auto IsPathExists(const std::string &path) -> bool;
    void AssertPathExists(const std::string &path);

    auto IsFileExists(const std::string &path) -> bool;
    auto IsDirExists(const std::string &path) -> bool;

    void AssertFileExists(const std::string &path);
    void AssertFileNotExists(const std::string &path);
    void AssertDirExists(const std::string &path);
    void AssertDirNotExists(const std::string &path);

    auto CheckFileExtension(const std::string &path, const std::string &extension) -> bool;

    auto ListDir(const std::string &path) -> std::unique_ptr<std::vector<std::string>>;
    auto ListDirsInDir(const std::string &path) -> std::unique_ptr<std::vector<std::string>>;
    auto ListFilesInDir(const std::string &path) -> std::unique_ptr<std::vector<std::string>>;
    auto ListFilesInDir(const std::string &path, const std::string &extension) -> std::unique_ptr<std::vector<std::string>>;

    auto IsDirEmpty(const std::string &path) -> bool;
    void AssertDirEmpty(const std::string &path);

    void MakeDir(const std::string &path);
    void RemoveDir(const std::string &path);

    void CreateEmptyFile(const std::string &path);
    void RemoveFile(const std::string &path);
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
