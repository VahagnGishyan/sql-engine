
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "app-info/application.hpp"
#include "dir-preparation.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::JSONQueryParser
{
    class TestDirPeparation
    {
       protected:
        TestDirPeparation()
        {
            m_path = Application::GetInfo().GetDefaultAppData() +
                     "/test-json-query-parer";
            ClearRemainingTempFilesAt(m_path);
            // Create test directory
            SQLEngine::Testing::JSONQueryParser::Preparation::InitAt(m_path);
            std::cout << "test-json-query-parser-dir:     " << m_path
                      << std::endl;
        }
        ~TestDirPeparation()
        {
            // // Destroy test directory
            // ClearRemainingTempFilesAt(m_path);
        }

       protected:
        static void ClearRemainingTempFilesAt(const std::string &path)
        {
            SQLEngine::Utility::RemoveDir(path,
                                          Utility::Option::MustExist{false});
        }

        //////////////////////////////////////////////////////////////////

       public:
        static void SetUp()
        {
            static TestDirPeparation obj;
        }

       protected:
        std::string m_path;
    };
}  // namespace SQLEngine::Testing::JSONQueryParser

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    try
    {
        SQLEngine::Testing::JSONQueryParser::TestDirPeparation::SetUp();
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    catch (const std::exception &e)
    {
        fmt::println(
            "tester-json-query-parser::main() UNHANDLED EXCEPTION: message: "
            "{}",
            e.what());
        return 1;
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
