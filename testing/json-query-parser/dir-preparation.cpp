
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "dir-preparation.hpp"

#include <fmt/core.h>

#include <iostream>

#include "database/database.hpp"
#include "dir-preparation-impl.hpp"
#include "local-database/db-local-json-stream.hpp"
#include "testing/json-query-parser/dir-preparation-impl.hpp"
#include "testing/json-query-parser/dir-preparation.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::JSONQueryParser
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PreparedDirWrapper
    {
       public:
        static void InitAt(const std::string& path)
        {
            Utility::Assert(
                s_peparator == nullptr,
                "PreparedDir::InitAt(...), s_peparator is not nullptr");

            Utility::MakeDir(path, Utility::Option::ExistOk{true},
                             Utility::Option::CreateBaseDirectory{false});

            Utility::AssertDirEmpty(path);
            s_peparator = Peparation::CreatePreparedDir(path);
        }

        static auto GetPreparedDir() -> const Peparation::IPreparedDir&
        {
            return *s_peparator;
        }

       protected:
        static Peparation::UPreparedDir s_peparator;
    };

    Peparation::UPreparedDir PreparedDirWrapper::s_peparator = nullptr;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Peparation::InitAt(const std::string& path)
    {
        PreparedDirWrapper::InitAt(path);
    }

    auto Peparation::GetEmptyDir() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetEmptyDir();
    }

    //////////////////////////////////////////////////////////////////////

    auto Peparation::GetDatabase() -> Interface::UDataBase
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetDatabase();
    }

    //////////////////////////////////////////////////////////////////////

    auto Peparation::GetInsertJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetInsertIntoJSONFileExample();
    }
    auto Peparation::GetUpdateJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetUpdateJSONFileExample();
    }
    auto Peparation::GetSelectJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetSelectJSONFileExample();
    }
    auto Peparation::GetDeleteJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetDeleteJSONFileExample();
    }

    //////////////////////////////////////////////////////////////////////

    auto Peparation::GetInsertJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetInsertJSONExamples();
    }
    auto Peparation::GetUpdateJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetUpdateJSONExamples();
    }
    auto Peparation::GetSelectJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetSelectJSONExamples();
    }
    auto Peparation::GetDeleteJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetDeleteJSONExamples();
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
