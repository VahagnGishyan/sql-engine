
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

TEST(IsDirEmpty, EmptyDirectory)
{
    auto &&testdir = Peparation::GetTestDir();
    const std::string emptyDir = testdir.GetEmptyDirPath();

    ASSERT_TRUE(IsDirEmpty(emptyDir));

    // Ensure that AssertDirEmpty does not throw an exception for an empty directory
    ASSERT_NO_THROW(AssertDirEmpty(emptyDir));
}

TEST(IsDirEmpty, NotEmptyDirectory)
{
    auto &&testdir = Peparation::GetTestDir();
    const std::string nonEmptyDir = testdir.GetWorkDir();
    const std::string nfile = testdir.GetFileNPath();
    const std::string ndir = testdir.GetDirNPath();

    EXPECT_FALSE(IsDirEmpty(nonEmptyDir));
    EXPECT_FALSE(IsDirEmpty(nfile));
    EXPECT_FALSE(IsDirEmpty(ndir));

    // Ensure that AssertDirEmpty throws an exception for a non-empty directory
    EXPECT_THROW(AssertDirEmpty(nonEmptyDir), std::runtime_error);
    EXPECT_THROW(AssertDirEmpty(nfile), std::runtime_error);
    EXPECT_THROW(AssertDirEmpty(ndir), std::runtime_error);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////