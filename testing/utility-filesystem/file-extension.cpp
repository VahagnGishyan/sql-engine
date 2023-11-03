
#include "utility/filesystem.hpp"
#include "test-dir-preparation.hpp"

#include <gtest/gtest.h>
#include <fmt/core.h>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine::Testing;
using namespace SQLEngine::Utility;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(AssertThrowFileExtensionTest, InvalidFileExtension)
{
    std::string validFilePath = "/path/to/file.txt";
    std::string validExtension = "txt";
    ASSERT_THROW(CheckFileExtension(validFilePath, validExtension), std::invalid_argument);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(CheckFileExtensionTest, ValidFileExtension)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&paeinfo = dir.GetValidFilePAEList();
    auto &&path = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&filepath = path + '/' + item.filename;
        EXPECT_TRUE(CheckFileExtension(filepath, item.extension))
            << fmt::format("CheckFileExtension(filepath: {}, extension: {})", filepath, item.extension);
    }
}

TEST(CheckFileExtensionTest, InvalidFileExtension)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&paeinfo = dir.GetValidFilePAEList();
    auto &&path = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&filepath = path + '/' + item.filename;
        auto &&extension = "aaa__";
        EXPECT_FALSE(CheckFileExtension(filepath, extension));
    }
}

TEST(CheckFileExtensionTest, NonExistingFiles)
{
    auto &&dir = DirPeparation::GetTestDir();
    auto &&paeinfo = dir.GetInvalidFilePAEList();
    auto &&path = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&filepath = path + '/' + item.filename;
        EXPECT_THROW(CheckFileExtension(filepath, item.extension), std::invalid_argument)
            << fmt::format("CheckFileExtension(filepath: {}, extension: {})", filepath, item.extension);
        ;
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////