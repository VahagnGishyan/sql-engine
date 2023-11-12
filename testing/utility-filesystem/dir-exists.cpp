
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

TEST(IsDirExistsTest, ExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_TRUE(IsDirExists(existingDirPath));
}

TEST(IsDirExistsTest, NonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_FALSE(IsDirExists(nonExistingPath));
    std::string nonExistingDirPath = "/path/to/nonexisting/dir.txt";
    ASSERT_FALSE(IsDirExists(nonExistingDirPath));
}

TEST(AssertDirExistsTest, ExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_NO_THROW(AssertDirExists(existingDirPath));
}

TEST(AssertDirExistsTest, NonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_THROW(AssertDirExists(nonExistingPath), std::exception);
}

TEST(AssertDirNotExistsTest, ExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_THROW(AssertDirNotExists(existingDirPath), std::exception);
}

TEST(AssertDirNotExistsTest, NonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertDirNotExists(nonExistingPath));
}

TEST(AssertDirNotExistsTest, BaseDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertDirNotExists(nonExistingPath));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(GetBaseDir, ExistingDir)
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

TEST(GetBaseDir, NonExistingDir)
{
    EXPECT_EQ(GetBaseDir("/path/to/some/directory/"), "/path/to/some");
    EXPECT_EQ(GetBaseDir("/path/to/some/directory"), "/path/to/some");
}

//////////////////////////////////////////////////////////////////////////

TEST(GetBaseDir, EmptyPathTest)
{
    const std::string path = "";
    EXPECT_THROW(GetBaseDir(path), std::exception);
}

TEST(GetBaseDir, NoSlashesTest)
{
    const std::string path = "file.txt";
    EXPECT_THROW(GetBaseDir(path), std::exception);
}

TEST(GetBaseDir, SingleSlashTest)
{
    const std::string path = "/";
    EXPECT_THROW(GetBaseDir(path), std::exception);
}

TEST(GetBaseDir, RelativePathTest)
{
    const std::string path = "../parent/child/file.txt";
    EXPECT_EQ(GetBaseDir(path), "../parent/child");
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////