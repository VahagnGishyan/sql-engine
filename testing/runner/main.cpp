
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "utility/filesystem.hpp"
#include "utility/test-dir-preparation.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing
{
    namespace Peparation
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
    }  // namespace Peparation
}  // namespace SQLEngine::Testing

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    SQLEngine::Testing::Peparation::SetUp();

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
