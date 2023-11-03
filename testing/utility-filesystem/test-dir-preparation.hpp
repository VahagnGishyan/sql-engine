
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>
#include <memory>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::DirPeparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class TestDir
    {
    public:
        virtual auto GetWorkDir() const -> const std::string = 0;
        virtual auto GetEmptyDirPath() const -> const std::string = 0;
        virtual auto GetFile1Path() const -> const std::string = 0;
        virtual auto GetEmptyFilePath() const -> const std::string = 0;
        virtual auto GetFileNPath() const -> const std::string = 0;
        virtual auto GetDirNPath() const -> const std::string = 0;
        virtual auto GetCompDirPath() const -> const std::string = 0;
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

        virtual auto GetValidFilePAEList() const -> const ShDirOfPAE = 0;
        virtual auto GetInvalidFilePAEList() const -> const ShDirOfPAE = 0;
    };

    //////////////////////////////////////////////////////////////////////

    auto GetTestDir() -> const TestDir &;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
