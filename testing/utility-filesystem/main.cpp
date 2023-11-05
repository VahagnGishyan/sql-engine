
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "test-dir-preparation.hpp"
#include "utility/filesystem.hpp"
#include <gtest/gtest.h>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Peparation
{
    void SetUp()
    {
        auto &&dir = Peparation::GetTestDir();
        std::cout << "testing-dir:     " << dir.GetWorkDir() << std::endl;
    }

    int ClearRemainingTempFiles()
    {
        auto &&testdir = Peparation::TestDir::GetTestingWorkDir();
        auto &&testname = Peparation::TestDir::GetTestingName();
        SQLEngine::Utility::RemoveDir(testdir + '/' + testname);
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    // return SQLEngine::Testing::Peparation::ClearRemainingTempFiles();

    SQLEngine::Testing::Peparation::SetUp();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
