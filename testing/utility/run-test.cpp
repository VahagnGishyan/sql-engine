
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "run-test.hpp"

#include <iostream>

#include "logging/logging.hpp"
#include "test-dir-preparation.hpp"
#include "utility/filesystem.hpp"

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

    void Utility::AddTests()
    {
        Logging::Signal("Add tests utility");
        SQLEngine::Testing::Peparation::SetUp();
    }
}  // namespace SQLEngine::Testing

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
