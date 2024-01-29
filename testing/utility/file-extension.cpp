
#include <fmt/core.h>
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

TEST(Utility, AssertThrowFileExtensionTest_InvalidFileExtension)
{
    std::string filepath = "/path/to/file.txt";
    EXPECT_TRUE(CheckFileExtension(filepath, "txt"));
    EXPECT_TRUE(CheckFileExtension(filepath, ".txt"));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Utility, CheckFileExtensionTest_ValidFileExtension)
{
    auto &&dir     = Peparation::GetTestDir();
    auto &&paeinfo = dir.GetValidFilePAEList();
    auto &&path    = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&filepath = path + '/' + item.filename;
        EXPECT_TRUE(CheckFileExtension(filepath, item.extension))
            << fmt::format("CheckFileExtension(filepath: {}, extension: {})",
                           filepath, item.extension);
    }
}

TEST(Utility, CheckFileExtensionTest_InvalidFileExtension)
{
    auto &&dir     = Peparation::GetTestDir();
    auto &&paeinfo = dir.GetValidFilePAEList();
    auto &&path    = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&filepath  = path + '/' + item.filename;
        auto &&extension = "aaa__";
        EXPECT_FALSE(CheckFileExtension(filepath, extension));
    }
}

TEST(Utility, CheckFileExtensionTest_NonExistingFiles)
{
    auto &&dir     = Peparation::GetTestDir();
    auto &&paeinfo = dir.GetInvalidFilePAEList();
    auto &&path    = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&filepath = path + '/' + item.filename;
        EXPECT_FALSE(CheckFileExtension(filepath, item.extension));
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////