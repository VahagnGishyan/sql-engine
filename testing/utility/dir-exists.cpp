
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

TEST(Utility, IsDirExists_TestExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_TRUE(IsDirExists(existingDirPath));
}

TEST(Utility, IsDirExists_TestNonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_FALSE(IsDirExists(nonExistingPath));
    std::string nonExistingDirPath = "/path/to/nonexisting/dir.txt";
    ASSERT_FALSE(IsDirExists(nonExistingDirPath));
}

TEST(Utility, AssertDirExistsTest_ExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_NO_THROW(AssertDirExists(existingDirPath));
}

TEST(Utility, AssertDirExistsTest_NonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_THROW(AssertDirExists(nonExistingPath), std::exception);
}

TEST(Utility, AssertDirNotExistsTest_ExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_THROW(AssertDirNotExists(existingDirPath), std::exception);
}

TEST(Utility, AssertDirNotExistsTest_NonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertDirNotExists(nonExistingPath));
}

TEST(Utility, AssertDirNotExistsTest_BaseDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertDirNotExists(nonExistingPath));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Utility, GetBaseDir_ExistingDir)
{
    auto &&dir = Peparation::GetTestDir();
    std::vector<std::string> list;
    list.reserve(5);
    list.push_back(dir.GetCompDirPath());
    list.push_back(dir.GetWorkDir());
    list.push_back(dir.GetEmptyDirPath());
    list.push_back(dir.GetFileNPath());
    list.push_back(dir.GetTestingWorkDir());
    for (auto &&path : list)
    {
        EXPECT_NO_THROW(AssertDirExists(GetBaseDir(path)));
    }
}

TEST(Utility, GetBaseDir_NonExistingDir)
{
    EXPECT_EQ(GetBaseDir("/path/to/some/directory/"), "/path/to/some");
    EXPECT_EQ(GetBaseDir("/path/to/some/directory"), "/path/to/some");
}

//////////////////////////////////////////////////////////////////////////

TEST(Utility, GetBaseDir_EmptyPathTest)
{
    const std::string path = "";
    EXPECT_THROW(GetBaseDir(path), std::exception);
}

TEST(Utility, GetBaseDir_NoSlashesTest)
{
    const std::string path = "file.txt";
    EXPECT_THROW(GetBaseDir(path), std::exception);
}

TEST(Utility, GetBaseDir_SingleSlashTest)
{
    const std::string path = "/";
    EXPECT_THROW(GetBaseDir(path), std::exception);
}

TEST(Utility, GetBaseDir_RelativePathTest)
{
    const std::string path = "../parent/child/file.txt";
    EXPECT_EQ(GetBaseDir(path), "../parent/child");
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////