
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "dir-preparation.hpp"
// #include "query/condition.hpp"
#include "query-parser/parsers.hpp"

/*temp*/
#include "debug-db/debug-db.hpp"
#include "local-database/db-local-json-stream.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// using namespace SQLEngine::Query;
using namespace SQLEngine;
using namespace SQLEngine::Interface;
using namespace SQLEngine::Testing::JSONQueryParser;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DeleteQuery, ExampleOfDeleteQuery)
{
    auto workdir            = Utility::GetBaseDir(Peparation::GetEmptyDir());
    auto database           = Peparation::GetDatabase();
    auto deleteQueryExample = Peparation::GetDeleteJSONFileExample();
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto&& query = QueryParser::CreateFromJSONFile(deleteQueryExample);
    DebugDB::PrintDataBase(*database);

    query->Execute(*database);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto filename = Utility::ExtractName(deleteQueryExample,
                                         Utility::Option::MustExist{false});
    filename      = Utility::RemoveExtensionFromFilename(
        filename, Utility::Option::MustExist{false});

    database->SetName(filename);
    auto writer = LocalDataBase::CreateDBLocalJSONWriter(workdir + "/output");
    writer->Write(*database);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
