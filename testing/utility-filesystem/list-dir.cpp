
#include <fmt/core.h>
#include <gtest/gtest.h>

#include <algorithm>
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

auto AreVectorsEqual(std::vector<std::string> first,
                     std::vector<std::string> second)
{
    // Create copies of the input lists to sort
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    // Compare the sorted lists element by element
    return first == second;
}

auto VecStrToStrForPrint(const std::vector<std::string> &list)
{
    std::string result = "[ ";
    for (auto &&item : list)
    {
        result += "{ " + item + " } ";
    }
    result += "]";
    return result;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(ListDir, ValidDirectory)
{
    auto &&testdir   = Peparation::GetTestDir();
    auto &&fileNpath = testdir.GetFileNPath();
    auto &&dirNpath  = testdir.GetDirNPath();
    auto &&compPath  = testdir.GetCompDirPath();

    auto &&fileNinfo = testdir.GetFileNInfo();
    auto &&dirNinfo  = testdir.GetDirNInfo();

    auto &&fileNList = ListDir(fileNpath);
    ASSERT_TRUE(fileNList != nullptr);
    ASSERT_EQ(fileNList->size(), fileNinfo->filenameList.size());
    EXPECT_TRUE(AreVectorsEqual(*fileNList, fileNinfo->filenameList));
    //  << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*fileNList),
    //  VecStrToStrForPrint(fileNinfo->filenameList));

    auto &&dirNList = ListDir(dirNpath);
    ASSERT_TRUE(dirNList != nullptr);
    ASSERT_EQ(dirNList->size(), dirNinfo->dirnameList.size());
    EXPECT_TRUE(AreVectorsEqual(*dirNList, dirNinfo->dirnameList));
    //  << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*fileNList),
    //  VecStrToStrForPrint(fileNinfo->filenameList));

    auto &&compList = ListDir(compPath);
    ASSERT_TRUE(compList != nullptr);
    EXPECT_EQ(compList->size(),
              fileNinfo->filenameList.size() + dirNinfo->dirnameList.size());
    //  << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*fileNList),
    //  VecStrToStrForPrint(fileNinfo->filenameList));
}

TEST(ListDir, EmptyDirectory)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    auto result = ListDir(emptydir);
    ASSERT_TRUE(result != nullptr);
    ASSERT_TRUE(result->empty());

    auto resultfiles = ListDirsInDir(emptydir);
    ASSERT_TRUE(resultfiles != nullptr);
    ASSERT_TRUE(resultfiles->empty());

    auto resultdir = ListFilesInDir(emptydir);
    ASSERT_TRUE(resultdir != nullptr);
    ASSERT_TRUE(resultdir->empty());
}

TEST(ListDirsInDir, ValidDirectory)
{
    auto &&testdir   = Peparation::GetTestDir();
    auto &&fileNpath = testdir.GetFileNPath();
    auto &&dirNpath  = testdir.GetDirNPath();
    auto &&compPath  = testdir.GetCompDirPath();

    auto &&fileNinfo = testdir.GetFileNInfo();
    auto &&dirNinfo  = testdir.GetDirNInfo();

    auto &&fileNList = ListDirsInDir(fileNpath);
    ASSERT_TRUE(fileNList != nullptr);
    EXPECT_EQ(fileNList->size(), 0);

    auto &&dirNList = ListDirsInDir(dirNpath);
    ASSERT_TRUE(dirNList != nullptr);
    ASSERT_EQ(dirNList->size(), dirNinfo->dirnameList.size());
    EXPECT_TRUE(AreVectorsEqual(*dirNList, dirNinfo->dirnameList))
        << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*dirNList),
                       VecStrToStrForPrint(dirNinfo->dirnameList));

    auto &&compList = ListDirsInDir(compPath);
    ASSERT_TRUE(compList != nullptr);
    EXPECT_EQ(compList->size(), dirNinfo->dirnameList.size());
}

TEST(ListFilesInDir, ValidDirectory)
{
    auto &&testdir   = Peparation::GetTestDir();
    auto &&fileNpath = testdir.GetFileNPath();
    auto &&dirNpath  = testdir.GetDirNPath();
    auto &&compPath  = testdir.GetCompDirPath();

    auto &&fileNinfo = testdir.GetFileNInfo();
    auto &&dirNinfo  = testdir.GetDirNInfo();

    auto &&fileNList = ListFilesInDir(fileNpath);
    ASSERT_TRUE(fileNList != nullptr);
    ASSERT_EQ(fileNList->size(), fileNinfo->filenameList.size());
    EXPECT_TRUE(AreVectorsEqual(*fileNList, fileNinfo->filenameList));

    auto &&dirNList = ListFilesInDir(dirNpath);
    ASSERT_TRUE(dirNList != nullptr);
    EXPECT_EQ(dirNList->size(), 0);

    auto &&compList = ListFilesInDir(compPath);
    ASSERT_TRUE(compList != nullptr);
    EXPECT_EQ(compList->size(), fileNinfo->filenameList.size());
}

TEST(ListDir, NonExistentDirectory)
{
    auto &&testdir     = Peparation::GetTestDir();
    auto &&nonExisting = testdir.GetNonExistingPath();

    ASSERT_THROW(ListDir(nonExisting), std::exception);
    ASSERT_THROW(ListDirsInDir(nonExisting), std::exception);
    ASSERT_THROW(ListFilesInDir(nonExisting), std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(ListFilesInDir, ListFilesWithExtension)
{
    auto &&testdir = Peparation::GetTestDir();
    auto &&paeinfo = testdir.GetValidFilePAEList();

    auto &&path = paeinfo->dirpath;
    for (auto &&item : paeinfo->paelist)
    {
        auto &&extension = item.extension;
        auto &&list = ListFilesInDir(path, extension, Option::FullPaths{true});
        ASSERT_NE(list, nullptr);
        for (auto &&file : *list)
        {
            EXPECT_TRUE(CheckFileExtension(file, extension))
                << fmt::format("file-path: {}, extension: {}", file, extension);
        }
    }
}

TEST(ListFilesInDir, ListFilesWithExtensionEmptyDir)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    auto &&extension = ".txt";
    auto &&list      = ListFilesInDir(emptydir, extension);
    ASSERT_NE(list, nullptr);
    ASSERT_EQ(list->size(), 0);
}

TEST(ListFilesInDir, ListFilesWithNonExistentDir)
{
    auto &&testdir     = Peparation::GetTestDir();
    auto &&nonExisting = testdir.GetNonExistingPath();

    auto &&extension = ".txt";
    ASSERT_THROW(ListFilesInDir(nonExisting, extension), std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(ListDir, OptionFullPathsFalseValidDirectory)
{
    auto &&testdir   = Peparation::GetTestDir();
    auto &&fileNpath = testdir.GetFileNPath();
    auto &&dirNpath  = testdir.GetDirNPath();
    auto &&compPath  = testdir.GetCompDirPath();

    auto &&fileNinfo = testdir.GetFileNInfo();
    auto &&dirNinfo  = testdir.GetDirNInfo();

    auto &&fileNList = ListDir(fileNpath, Option::FullPaths{false});
    ASSERT_TRUE(fileNList != nullptr);
    ASSERT_EQ(fileNList->size(), fileNinfo->filenameList.size());
    EXPECT_TRUE(AreVectorsEqual(*fileNList, fileNinfo->filenameList));
    //  << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*fileNList),
    //  VecStrToStrForPrint(fileNinfo->filenameList));

    auto &&dirNList = ListDir(dirNpath, Option::FullPaths{false});
    ASSERT_TRUE(dirNList != nullptr);
    ASSERT_EQ(dirNList->size(), dirNinfo->dirnameList.size());
    EXPECT_TRUE(AreVectorsEqual(*dirNList, dirNinfo->dirnameList));
    //  << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*fileNList),
    //  VecStrToStrForPrint(fileNinfo->filenameList));

    auto &&compList = ListDir(compPath, Option::FullPaths{false});
    ASSERT_TRUE(compList != nullptr);
    EXPECT_EQ(compList->size(),
              fileNinfo->filenameList.size() + dirNinfo->dirnameList.size());
    //  << fmt::format("first: {}, second: {}", VecStrToStrForPrint(*fileNList),
    //  VecStrToStrForPrint(fileNinfo->filenameList));

    for (auto &&path : *fileNList)
    {
        EXPECT_EQ(GetBaseDir(path, Option::MustExist{false}), "");
    }
}

TEST(ListDir, OptionFullPathsTrueValidDirectory)
{
    auto &&testdir   = Peparation::GetTestDir();
    auto &&fileNpath = testdir.GetFileNPath();
    auto &&dirNpath  = testdir.GetDirNPath();
    auto &&compPath  = testdir.GetCompDirPath();

    auto &&fileNinfo = testdir.GetFileNInfo();
    auto &&dirNinfo  = testdir.GetDirNInfo();

    auto &&fileNList = ListDir(fileNpath, Option::FullPaths{true});
    ASSERT_TRUE(fileNList != nullptr);
    ASSERT_EQ(fileNList->size(), fileNinfo->filenameList.size());

    auto &&dirNList = ListDir(dirNpath, Option::FullPaths{false});
    ASSERT_TRUE(dirNList != nullptr);
    ASSERT_EQ(dirNList->size(), dirNinfo->dirnameList.size());

    auto &&compList = ListDir(compPath, Option::FullPaths{false});
    ASSERT_TRUE(compList != nullptr);
    EXPECT_EQ(compList->size(),
              fileNinfo->filenameList.size() + dirNinfo->dirnameList.size());

    for (auto &&path : *fileNList)
    {
        EXPECT_NO_THROW(GetBaseDir(path, Option::MustExist{true}));
    }
}

TEST(ListDir, OptionFullPathsFalseEmptyDirectory)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    auto result = ListDir(emptydir, Option::FullPaths{false});
    ASSERT_TRUE(result != nullptr);
    ASSERT_TRUE(result->empty());

    auto resultfiles = ListDirsInDir(emptydir, Option::FullPaths{false});
    ASSERT_TRUE(resultfiles != nullptr);
    ASSERT_TRUE(resultfiles->empty());

    auto resultdir = ListFilesInDir(emptydir, Option::FullPaths{false});
    ASSERT_TRUE(resultdir != nullptr);
    ASSERT_TRUE(resultdir->empty());
}

TEST(ListDir, OptionFullPathsTrueEmptyDirectory)
{
    auto &&testdir  = Peparation::GetTestDir();
    auto &&emptydir = testdir.GetEmptyDirPath();

    auto result = ListDir(emptydir, Option::FullPaths{true});
    ASSERT_TRUE(result != nullptr);
    ASSERT_TRUE(result->empty());

    auto resultfiles = ListDirsInDir(emptydir, Option::FullPaths{false});
    ASSERT_TRUE(resultfiles != nullptr);
    ASSERT_TRUE(resultfiles->empty());

    auto resultdir = ListFilesInDir(emptydir, Option::FullPaths{false});
    ASSERT_TRUE(resultdir != nullptr);
    ASSERT_TRUE(resultdir->empty());
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////