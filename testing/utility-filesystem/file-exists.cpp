
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

TEST(IsFileExistsTest, ExistingFile)
{
    auto &&dir              = Peparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_TRUE(IsFileExists(existingFilePath));
}

TEST(IsFileExistsTest, NonExistingFile)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&workdir         = dir.GetWorkDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_FALSE(IsFileExists(nonExistingPath));
    std::string nonExistingFilePath = "/path/to/nonexisting/file.txt";
    ASSERT_FALSE(IsFileExists(nonExistingFilePath));
}

TEST(AssertFileExistsTest, ExistingFile)
{
    auto &&dir              = Peparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_NO_THROW(AssertFileExists(existingFilePath));
}

TEST(AssertFileExistsTest, NonExistingFile)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_THROW(AssertFileExists(nonExistingPath), std::exception);
}

TEST(AssertFileNotExistsTest, ExistingFile)
{
    auto &&dir              = Peparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_THROW(AssertFileNotExists(existingFilePath), std::exception);
}

TEST(AssertFileNotExistsTest, NonExistingFile)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertFileNotExists(nonExistingPath));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////