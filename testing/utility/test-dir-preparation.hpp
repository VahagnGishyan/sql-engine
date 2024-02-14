
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Preparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class TestDir
    {
       public:
        virtual ~TestDir() = default;

       public:
        static auto GetTestingWorkDir() -> const std::string;
        static auto GetTestingName() -> const std::string;

       public:
        virtual auto GetWorkDir() const -> const std::string       = 0;
        virtual auto GetEmptyDirPath() const -> const std::string  = 0;
        virtual auto GetFile1Path() const -> const std::string     = 0;
        virtual auto GetEmptyFilePath() const -> const std::string = 0;

        struct FileNInfo
        {
            std::vector<std::string> filenameList;
        };
        using ShFileNInfo = std::shared_ptr<FileNInfo>;
        virtual auto GetFileNInfo() const -> const ShFileNInfo = 0;

        struct DirNInfo
        {
            std::vector<std::string> dirnameList;
        };
        using ShDirNInfo = std::shared_ptr<DirNInfo>;
        virtual auto GetDirNInfo() const -> const ShDirNInfo = 0;

        virtual auto GetFileNPath() const -> const std::string       = 0;
        virtual auto GetDirNPath() const -> const std::string        = 0;
        virtual auto GetCompDirPath() const -> const std::string     = 0;
        virtual auto GetNonExistingPath() const -> const std::string = 0;

        struct PathAndExtension
        {
            std::string filename;
            std::string extension;
        };
        using PathAndExtList = std::vector<PathAndExtension>;
        struct DirOfPAE
        {
            std::string dirpath;
            PathAndExtList paelist;
        };
        using ShDirOfPAE = std::shared_ptr<DirOfPAE>;

        virtual auto GetValidFilePAEList() const -> const ShDirOfPAE   = 0;
        virtual auto GetInvalidFilePAEList() const -> const ShDirOfPAE = 0;

        virtual void Create()  = 0;
        virtual void Destroy() = 0;
    };

    //////////////////////////////////////////////////////////////////////

    auto GetTestDirManager() -> TestDir &;
    auto GetTestDir() -> const TestDir &;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
