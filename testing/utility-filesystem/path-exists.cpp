
#include <gtest/gtest.h>
#include "utility/filesystem.hpp"
#include "test-dir-preparation.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine::Testing;
using namespace SQLEngine::Utility;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(IsPathExistsTest, ExistingPath)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&workdir = dir.GetWorkDir();
    auto &&emptydir = dir.GetEmptyDirPath();
    auto &&file1 = dir.GetFile1Path();
    auto &&fileN = dir.GetFileNPath();
    auto &&dirN = dir.GetDirNPath();
    auto &&comp = dir.GetFileNDirNPath();
    ASSERT_TRUE(IsPathExists(workdir));
    ASSERT_TRUE(IsPathExists(emptydir));
    ASSERT_TRUE(IsPathExists(file1));
    ASSERT_TRUE(IsPathExists(fileN));
    ASSERT_TRUE(IsPathExists(dirN));
    ASSERT_TRUE(IsPathExists(comp));
}

TEST(IsPathExistsTest, NonExistingPath)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&workdir = dir.GetWorkDir();
    auto &&nonExistingPath = workdir + "/__nonexisting__";
    ASSERT_FALSE(IsPathExists(nonExistingPath));
}

TEST(AssertPathExistsTest, ExistingPath)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&workdir = dir.GetWorkDir();
    ASSERT_NO_THROW(AssertPathExists(workdir));
}

TEST(AssertPathExistsTest, NonExistingPath)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&workdir = dir.GetWorkDir();
    auto &&nonExistingPath = workdir + "/__nonexisting__";
    ASSERT_THROW(AssertPathExists(nonExistingPath), std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////