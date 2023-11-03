
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

TEST(IsFileExistsTest, ExistingFile)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_TRUE(IsFileExists(existingFilePath));
}

TEST(IsFileExistsTest, NonExistingFile)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&workdir = dir.GetWorkDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_FALSE(IsFileExists(nonExistingPath));
    std::string nonExistingFilePath = "/path/to/nonexisting/file.txt";
    ASSERT_FALSE(IsFileExists(nonExistingFilePath));
}

TEST(AssertFileExistsTest, ExistingFile)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_NO_THROW(AssertFileExists(existingFilePath));
}

TEST(AssertFileExistsTest, NonExistingFile)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_THROW(AssertFileExists(nonExistingPath), std::invalid_argument);
}

TEST(AssertFileNotExistsTest, ExistingFile)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_THROW(AssertFileNotExists(existingFilePath), std::invalid_argument);
}

TEST(AssertFileNotExistsTest, NonExistingFile)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertFileNotExists(nonExistingPath));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////