
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
            s_peparator = Preparation::CreatePreparedDir(path);
        }

        static auto GetPreparedDir() -> const Preparation::IPreparedDir&
        {
            return *s_peparator;
        }

       protected:
        static Preparation::UPreparedDir s_peparator;
    };

    Preparation::UPreparedDir PreparedDirWrapper::s_peparator = nullptr;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Preparation::InitAt(const std::string& path)
    {
        PreparedDirWrapper::InitAt(path);
    }

    auto Preparation::GetEmptyDir() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetEmptyDir();
    }

    auto Preparation::GetResultDir() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetResultDir();
    }

    //////////////////////////////////////////////////////////////////////

    auto Preparation::GetDatabase() -> Interface::UDataBase
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetDatabase();
    }

    //////////////////////////////////////////////////////////////////////

    auto Preparation::GetInsertJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetInsertIntoJSONFileExample();
    }
    auto Preparation::GetUpdateJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetUpdateJSONFileExample();
    }
    auto Preparation::GetSelectJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetSelectJSONFileExample();
    }
    auto Preparation::GetDeleteJSONFileExample() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetDeleteJSONFileExample();
    }

    //////////////////////////////////////////////////////////////////////

    auto Preparation::GetInsertJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetInsertJSONExamples();
    }
    auto Preparation::GetUpdateJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetUpdateJSONExamples();
    }
    auto Preparation::GetSelectJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetSelectJSONExamples();
    }
    auto Preparation::GetDeleteJSONExamples()
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
