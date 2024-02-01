
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "testing/utility/test-dir-preparation.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing
{
    class TestDirPeparation
    {
       protected:
        TestDirPeparation()
        {
            ClearRemainingTempFiles();
            // Create test directory
            auto &&dir = Peparation::GetTestDirManager();
            dir.Create();
        }
        ~TestDirPeparation()
        {
            // Destroy test directory
            ClearRemainingTempFiles();
        }

        static void ClearRemainingTempFiles()
        {
            auto &&testdir  = Peparation::TestDir::GetTestingWorkDir();
            auto &&testname = Peparation::TestDir::GetTestingName();
            SQLEngine::Utility::RemoveDir(testdir,
              Utility::Option::MustExist{false});
        }

        //////////////////////////////////////////////////////////////////

       public:
        static void SetUp()
        {
            static TestDirPeparation obj;
            auto &&dir = Peparation::GetTestDir();
            std::cout << "testing-dir:     " << dir.GetWorkDir() << std::endl;
        }
    };
}  // namespace SQLEngine::Testing

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    SQLEngine::Testing::TestDirPeparation::SetUp();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
