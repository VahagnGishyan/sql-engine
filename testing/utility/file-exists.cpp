
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

TEST(Utility, IsFileExistsTest_ExistingFile)
{
    auto &&dir              = Peparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_TRUE(IsFileExists(existingFilePath));
}

TEST(Utility, IsFileExistsTest_NonExistingFile)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&workdir         = dir.GetWorkDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_FALSE(IsFileExists(nonExistingPath));
    std::string nonExistingFilePath = "/path/to/nonexisting/file.txt";
    ASSERT_FALSE(IsFileExists(nonExistingFilePath));
}

TEST(Utility, AssertFileExistsTest_ExistingFile)
{
    auto &&dir              = Peparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_NO_THROW(AssertFileExists(existingFilePath));
}

TEST(Utility, AssertFileExistsTest_NonExistingFile)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_THROW(AssertFileExists(nonExistingPath), std::exception);
}

TEST(Utility, AssertFileNotExistsTest_ExistingFile)
{
    auto &&dir              = Peparation::GetTestDir();
    auto &&existingFilePath = dir.GetEmptyFilePath();
    ASSERT_THROW(AssertFileNotExists(existingFilePath), std::exception);
}

TEST(Utility, AssertFileNotExistsTest_NonExistingFile)
{
    auto &&dir             = Peparation::GetTestDir();
    auto &&nonExistingPath = dir.GetNonExistingPath();
    ASSERT_NO_THROW(AssertFileNotExists(nonExistingPath));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////