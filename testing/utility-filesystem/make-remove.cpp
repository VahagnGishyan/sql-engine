
#include <fmt/core.h>
#include <gtest/gtest.h>

#include <vector>

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

TEST(MakeAndRemoveDir, Success)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    const std::string testDir = emptydir + "/test-directory";

    // Ensure the directory does not exist initially
    ASSERT_FALSE(IsDirExists(testDir));

    // Create the directory
    ASSERT_NO_THROW(MakeDir(testDir));

    // Verify that the directory has been created
    EXPECT_TRUE(IsDirExists(testDir));

    // Remove the directory
    ASSERT_NO_THROW(RemoveDir(testDir));

    // Verify that the directory has been removed
    EXPECT_FALSE(IsDirExists(testDir));
}

TEST(MakeDir, Failure)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    const std::string existingDir = emptydir + "/existing_directory";

    // Create the existing directory
    MakeDir(existingDir);

    // Attempt to create the directory again (expecting an exception)
    ASSERT_THROW(MakeDir(existingDir), std::invalid_argument);

    // Ensure the directory still exists
    EXPECT_TRUE(IsDirExists(existingDir));

    // Attempt to remove a non-existing directory (expecting an exception)
    ASSERT_NO_THROW(RemoveDir(existingDir));

    // Ensure the directory still does not exist
    EXPECT_FALSE(IsDirExists(existingDir));
}

TEST(RemoveDir, Failure)
{
    auto &&testdir  = Peparation::GetTestDir();
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

TEST(MakeAndRemoveFile, Success)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    const std::string testFile = emptydir + "test-file.txt";

    // Ensure the file does not exist initially
    EXPECT_FALSE(IsFileExists(testFile));

    // Create the empty file
    EXPECT_NO_THROW(MakeEmptyFile(testFile));

    // Verify that the file has been created
    EXPECT_TRUE(IsFileExists(testFile));

    // Create the empty file
    EXPECT_NO_THROW(RemoveFile(testFile));
}

TEST(MakeFile, Failure)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    // Define an existing file path for testing (change it as needed)
    const std::string existingFile = emptydir + "existing-file.txt";

    // Create the existing file
    MakeEmptyFile(existingFile);

    // Attempt to create the file again (expecting an exception)
    EXPECT_THROW(MakeEmptyFile(existingFile), std::invalid_argument);

    // Ensure the file still exists
    EXPECT_TRUE(IsFileExists(existingFile));

    // Remove the file
    EXPECT_NO_THROW(RemoveFile(existingFile));

    // Verify that the file has been removed
    EXPECT_FALSE(IsFileExists(existingFile));
}

TEST(RemoveFile, Failure)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    // Define an existing file path for testing (change it as needed)
    const std::string nonExistingFile = emptydir + "non-existing-file.txt";

    // Attempt to remove a non-existing file (expecting an exception)
    ASSERT_THROW(RemoveFile(nonExistingFile), std::logic_error);

    // Ensure the file still does not exist
    ASSERT_FALSE(IsFileExists(nonExistingFile));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(MakeDirOption, ExistOkExisting)
{
    auto &&testdir = Peparation::GetTestDir();
    auto workdir   = testdir.GetWorkDir();

    ASSERT_TRUE(IsDirExists(workdir));
    EXPECT_NO_THROW(MakeDir(workdir, Option::ExistOk{true}));
    EXPECT_THROW(MakeDir(workdir, Option::ExistOk{false}), std::exception);
}

TEST(MakeDirOption, ExistOkNonExisting)
{
    auto &&testdir       = Peparation::GetTestDir();
    auto nonExistingPath = testdir.GetNonExistingPath();

    ASSERT_FALSE(IsDirExists(nonExistingPath));
    ASSERT_TRUE(IsDirExists(GetBaseDir(nonExistingPath)));
    EXPECT_NO_THROW(MakeDir(nonExistingPath, Option::ExistOk{false}));
    EXPECT_NO_THROW(MakeDir(nonExistingPath, Option::ExistOk{true}));
    ASSERT_NO_THROW(RemoveDir(nonExistingPath));
}

TEST(MakeDirOption, CreateBaseDirectoryExisting)
{
    auto &&testdir = Peparation::GetTestDir();
    auto workdir   = testdir.GetWorkDir();

    ASSERT_TRUE(IsDirExists(workdir));
    ASSERT_THROW(MakeDir(workdir, Option::ExistOk{false},
                         Option::CreateBaseDirectory{true}),
                 std::exception);
    ASSERT_NO_THROW(MakeDir(workdir, Option::ExistOk{true},
                            Option::CreateBaseDirectory{true}));
}

TEST(MakeDirOption, CreateBaseDirectoryNonExisting)
{
    auto &&testdir                 = Peparation::GetTestDir();
    auto nonExistingPath           = testdir.GetNonExistingPath();
    auto nonExistingChilds         = "/path/to/child/dir";
    auto nonExistingPathWithChilds = nonExistingPath + nonExistingChilds;

    ASSERT_FALSE(IsDirExists(nonExistingPath));
    ASSERT_FALSE(IsDirExists(nonExistingPathWithChilds));
    ASSERT_TRUE(IsDirExists(GetBaseDir(nonExistingPath)));
    ASSERT_THROW(MakeDir(nonExistingPathWithChilds, Option::ExistOk{true}),
                 std::exception);
    ASSERT_THROW(MakeDir(nonExistingPathWithChilds, Option::ExistOk{false}),
                 std::exception);
    ASSERT_THROW(MakeDir(nonExistingPathWithChilds, Option::ExistOk{false},
                         Option::CreateBaseDirectory{false}),
                 std::exception);

    EXPECT_NO_THROW(MakeDir(nonExistingPathWithChilds, Option::ExistOk{false},
                            Option::CreateBaseDirectory{true}));
    ASSERT_TRUE(IsDirExists(nonExistingPathWithChilds));
    ASSERT_NO_THROW(RemoveDir(nonExistingPath));
    ASSERT_FALSE(IsDirExists(nonExistingPathWithChilds));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
