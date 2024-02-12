
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

namespace SQLEngine::Testing::JSONQueryParser::Peparation
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
            s_peparator = CreatePreparedDir(path);
        }

        static auto GetPreparedDir() -> const IPreparedDir&
        {
            return *s_peparator;
        }

       protected:
        static UPreparedDir s_peparator;
    };

    UPreparedDir PreparedDirWrapper::s_peparator = nullptr;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void InitAt(const std::string& path)
    {
        PreparedDirWrapper::InitAt(path);
    }

    auto GetEmptyDir() -> const std::string
    {
        auto&& dir = PreparedDirWrapper::GetPreparedDir();
        return dir.GetEmptyDir();
    }

    auto GetSelectIntoJSONFileExample() -> const std::string;
    auto GetUpdateJSONFileExample() -> const std::string;
    auto GetSelectJSONFileExample() -> const std::string;
    auto GetDeleteJSONFileExample() -> const std::string;

    auto GetSelectIntoJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;
    auto GetUpdateJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;
    auto GetSelectJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;
    auto GetDeleteJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Peparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
