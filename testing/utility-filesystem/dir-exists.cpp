
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
    auto &&workdir         = dir.GetWorkDir();
    auto &&nonExistingPath = workdir + "/__nonexisting__";
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
    auto &&workdir         = dir.GetWorkDir();
    auto &&nonExistingPath = workdir + "/__nonexisting__";
    ASSERT_THROW(AssertDirExists(nonExistingPath), std::invalid_argument);
}

TEST(AssertDirNotExistsTest, ExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&existingDirPath = dir.GetEmptyDirPath();
    ASSERT_THROW(AssertDirNotExists(existingDirPath), std::invalid_argument);
}

TEST(AssertDirNotExistsTest, NonExistingDir)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&workdir         = dir.GetWorkDir();
    auto &&nonExistingPath = workdir + "/__nonexisting__";
    ASSERT_NO_THROW(AssertDirNotExists(nonExistingPath));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////