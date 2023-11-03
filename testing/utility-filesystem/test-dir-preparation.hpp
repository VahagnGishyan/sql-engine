
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>

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
