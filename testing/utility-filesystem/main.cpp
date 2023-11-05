
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "test-dir-preparation.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Peparation
{
    class TestDirWrapperAutoCreateDestroy
    {
       public:
        TestDirWrapperAutoCreateDestroy()
        {
            // Create test directory
            auto &&dir = Peparation::GetTestDirManager();
            dir.Create();
        }
        ~TestDirWrapperAutoCreateDestroy()
        {
            // Destroy test directory
            auto &&dir = Peparation::GetTestDirManager();
            dir.Destroy();
        }
    };

    void SetUp()
    {
        static TestDirWrapperAutoCreateDestroy obj;
        auto &&dir = Peparation::GetTestDir();
        std::cout << "testing-dir:     " << dir.GetWorkDir() << std::endl;
    }

    int ClearRemainingTempFiles()
    {
        auto &&testdir  = Peparation::TestDir::GetTestingWorkDir();
        auto &&testname = Peparation::TestDir::GetTestingName();
        SQLEngine::Utility::RemoveDir(testdir + '/' + testname);
        return 0;
    }
}  // namespace SQLEngine::Testing::Peparation

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
