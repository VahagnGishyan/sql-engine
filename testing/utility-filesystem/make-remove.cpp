
#include "utility/filesystem.hpp"
#include "test-dir-preparation.hpp"

#include <gtest/gtest.h>
#include <fmt/core.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine::Testing;
using namespace SQLEngine::Utility;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(UtilityTest, MakeAndRemoveDirSuccess)
{
    auto &&testdir = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    const std::string testDir = emptydir + "/test-directory";

    // Ensure the directory does not exist initially
    ASSERT_FALSE(IsDirExists(testDir));

    // Create the directory
    ASSERT_NO_THROW(MakeDir(testDir));

    // Create the directory, when it exists, must be correct output
    ASSERT_NO_THROW(MakeDir(testDir));

    // Verify that the directory has been created
    EXPECT_TRUE(IsDirExists(testDir));

    // Remove the directory
    ASSERT_NO_THROW(RemoveDir(testDir));

    // Verify that the directory has been removed
    EXPECT_FALSE(IsDirExists(testDir));
}

TEST(UtilityTest, RemoveDirFailure)
{
    auto &&testdir = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    const std::string testDir = emptydir + "/test-directory";

    // Attempt to remove a non-existing directory (expecting an exception)
    EXPECT_THROW(RemoveDir(testDir), std::invalid_argument);

    // Ensure the directory still does not exist
    EXPECT_FALSE(IsDirExists(testDir));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////