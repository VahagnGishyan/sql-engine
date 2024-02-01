
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "app-info/application.hpp"
#include "fmt/core.h"
#include "local-database/local-database.hpp"
#include "utility.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// static auto GetDefaultTestDir() -> const std::string
// {
//     struct Directory
//     {
//         Directory()
//         {
//             auto&& info       = Application::GetInfo();
//             auto&& appWorkDir = info.GetDefaultAppData();
//             path = fmt::format("{}/{}", appWorkDir, "testdir-local-db");
//             if (Utility::IsDirExists(path))
//             {
//                 Utility::ClearDirectoryContent(path);
//                 return;
//             }
//             Utility::MakeDir(path);
//         }
//         ~Directory()
//         {
//             Utility::RemoveDir(path, Utility::Option::MustExist(false));
//         }

//         auto GetPath() const -> std::string
//         {
//             Utility::ClearDirectoryContent(path);
//             return path;
//         }

//         std::string path;
//     };

//     static Directory dir;
//     return dir.GetPath();
// }

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// TEST(LocalDataBase, Init)
// {
//     auto&& testdir = GetDefaultTestDir();
//     ASSERT_NO_THROW(LocalDataBase::Init(testdir));
// }

//////////////////////////////////////////////////////////////////////////

// TEST(LocalDataBase, InvalidInit)
// {
//     std::string nonexitingPath = "";
//     ASSERT_THROW(LocalDataBase::Init(nonexitingPath),
//                  std::exception);
// }

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
