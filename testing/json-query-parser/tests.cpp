
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

void CheckQuery(const IDataBase& db, const std::string& queryPath)
{
    //////////////////////////////////////////////////////////////////////
    auto&& udatabase = db.Copy();
    auto&& database  = *udatabase;
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto&& query = QueryParser::CreateFromJSONFile(queryPath);
    query->Execute(database);
    //////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    auto&& resultdir             = Preparation::GetResultDir();
    auto&& filenameWithExtention = Utility::ExtractName(queryPath);
    auto&& filename =
        Utility::RemoveExtensionFromFilename(filenameWithExtention);
    auto&& resultDBPath = fmt::format("{}/{}", resultdir, filename);

    auto&& reader = LocalDataBase::CreateDBLocalJSONReader(resultDBPath);
    auto&& resultShouldBe = reader->Read();
    resultShouldBe->SetName(database.GetName());
    DebugDB::CheckDatabase(database, *resultShouldBe);
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST(JSONQueryParser, DeleteQuery)
{
    auto workdir  = Utility::GetBaseDir(Preparation::GetEmptyDir());
    auto database = Preparation::GetDatabase();
    auto&& list   = Preparation::GetDeleteJSONExamples();
    for (auto&& queryPath : *list)
    {
        EXPECT_NO_THROW(CheckQuery(*database, queryPath));
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(JSONQueryParser, InsertQuery)
{
    auto workdir  = Utility::GetBaseDir(Preparation::GetEmptyDir());
    auto database = Preparation::GetDatabase();
    auto&& list   = Preparation::GetInsertJSONExamples();
    for (auto&& queryPath : *list)
    {
        // fmt::println("vgishyan: path = {}", queryPath);
        EXPECT_NO_THROW(CheckQuery(*database, queryPath));
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(JSONQueryParser, SelectQuery)
{
    auto workdir  = Utility::GetBaseDir(Preparation::GetEmptyDir());
    auto database = Preparation::GetDatabase();
    auto&& list   = Preparation::GetSelectJSONExamples();
    for (auto&& queryPath : *list)
    {
        // fmt::println("vgishyan: path = {}", Utility::ExtractName(queryPath));
        EXPECT_NO_THROW(CheckQuery(*database, queryPath));
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

// TEST(JSONQueryParser, UpdateQuery)
// {
//     auto workdir  = Utility::GetBaseDir(Preparation::GetEmptyDir());
//     auto database = Preparation::GetDatabase();
//     auto&& list   = Preparation::GetUpdateJSONExamples();
//     for (auto&& queryPath : *list)
//     {
//         fmt::println("vgishyan: path = {}", Utility::ExtractName(queryPath));
//         EXPECT_NO_THROW(CheckQuery(*database, queryPath));
//     }
// }

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
