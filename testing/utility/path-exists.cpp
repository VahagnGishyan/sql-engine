
#include <gtest/gtest.h>

#include "test-dir-preparation.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine::Testing;
using namespace SQLEngine::Utility;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Utility, IsPathExistsTest_ExistingPath)
{
    auto &&dir      = Preparation::GetTestDir();
    auto &&workdir  = dir.GetWorkDir();
    auto &&emptydir = dir.GetEmptyDirPath();
    auto &&file1    = dir.GetFile1Path();
    auto &&fileN    = dir.GetFileNPath();
    auto &&dirN     = dir.GetDirNPath();
    auto &&comp     = dir.GetCompDirPath();
    ASSERT_TRUE(IsPathExists(workdir));
    ASSERT_TRUE(IsPathExists(emptydir));
    ASSERT_TRUE(IsPathExists(file1));
    ASSERT_TRUE(IsPathExists(fileN));
    ASSERT_TRUE(IsPathExists(dirN));
    ASSERT_TRUE(IsPathExists(comp));
}

TEST(Utility, IsPathExistsTest_NonExistingPath)
{
    auto &&dir             = Preparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_FALSE(IsPathExists(nonExistingPath));
}

TEST(Utility, AssertPathExistsTest_ExistingPath)
{
    auto &&dir     = Preparation::GetTestDir();
    auto &&workdir = dir.GetWorkDir();
    ASSERT_NO_THROW(AssertPathExists(workdir));
}

TEST(Utility, AssertPathExistsTest_NonExistingPath)
{
    auto &&dir             = Preparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_THROW(AssertPathExists(nonExistingPath), std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////