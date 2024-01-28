

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

#include "options.hpp"
#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Utility
{
    PROJECT_SHARED_EXPORT
    auto IsPathExists(const std::string &path) -> bool;
    PROJECT_SHARED_EXPORT
    void AssertPathExists(const std::string &path);
    PROJECT_SHARED_EXPORT
    auto IsPathAbsolute(const std::string &path) -> bool;
    PROJECT_SHARED_EXPORT
    void AssertPathAbsolute(const std::string &path);

    PROJECT_SHARED_EXPORT
    auto IsFileExists(const std::string &path) -> bool;
    PROJECT_SHARED_EXPORT
    auto IsDirExists(const std::string &path) -> bool;
    PROJECT_SHARED_EXPORT
    auto GetBaseDir(const std::string &path,
                    const Option::MustExist &mustexist = Option::MustExist{
                        true}) -> const std::string;

    PROJECT_SHARED_EXPORT
    void AssertFileExists(const std::string &path);
    PROJECT_SHARED_EXPORT
    void AssertFileNotExists(const std::string &path);
    PROJECT_SHARED_EXPORT
    void AssertDirExists(const std::string &path);
    PROJECT_SHARED_EXPORT
    void AssertDirNotExists(const std::string &path);

    PROJECT_SHARED_EXPORT
    auto CheckFileExtension(const std::string &path,
                            const std::string &extension) -> bool;

    PROJECT_SHARED_EXPORT
    auto ListDir(const std::string &path,
                 const Option::FullPaths returnFullPaths = Option::FullPaths{
                     false}) -> std::unique_ptr<std::vector<std::string>>;
    PROJECT_SHARED_EXPORT
    auto ListDirsInDir(
        const std::string &path,
        const Option::FullPaths returnFullPaths = Option::FullPaths{false})
        -> std::unique_ptr<std::vector<std::string>>;
    PROJECT_SHARED_EXPORT
    auto ListFilesInDir(
        const std::string &path,
        const Option::FullPaths returnFullPaths = Option::FullPaths{false})
        -> std::unique_ptr<std::vector<std::string>>;
    PROJECT_SHARED_EXPORT
    auto ListFilesInDir(
        const std::string &path, const std::string &extension,
        const Option::FullPaths returnFullPaths = Option::FullPaths{false})
        -> std::unique_ptr<std::vector<std::string>>;

    PROJECT_SHARED_EXPORT
    auto IsDirEmpty(const std::string &path) -> bool;
    PROJECT_SHARED_EXPORT
    void AssertDirEmpty(const std::string &path);

    PROJECT_SHARED_EXPORT
    void MakeDir(const std::string &path,
                 const Option::ExistOk existok = Option::ExistOk{false},
                 const Option::CreateBaseDirectory &createbase =
                     Option::CreateBaseDirectory{false});
    PROJECT_SHARED_EXPORT
    void RemoveDir(const std::string &path,
                   const Option::MustExist mustexist = Option::MustExist{true});

    PROJECT_SHARED_EXPORT
    void MakeEmptyFile(const std::string &path,
                       const Option::ExistOk existok = Option::ExistOk{false},
                       const Option::CreateBaseDirectory &createbase =
                           Option::CreateBaseDirectory{false});
    PROJECT_SHARED_EXPORT
    void RemoveFile(const std::string &path,
                    const Option::MustExist mustexist = Option::MustExist{
                        true});
}  // namespace SQLEngine::Utility

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
