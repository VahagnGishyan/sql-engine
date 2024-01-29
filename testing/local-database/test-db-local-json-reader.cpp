
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "app-info/application.hpp"
#include "local-database/db-local-json-stream.hpp"
#include "fmt/core.h"
#include "utility.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

static auto GetDefaultWorkDir() -> std::string
{
    auto&& info       = Application::GetInfo();
    auto&& appWorkDir = info.GetDefaultAppData();
    return fmt::format("{}/{}", appWorkDir, "testdir");
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBaseJSONWriter, InvalidCreation)
{
    std::string nonexitingPath = "";

    ASSERT_THROW(DBManager::CreateDBLocalJSONReader(nonexitingPath),
                 std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBaseJSONWriter, Creation)
{
    auto&& info       = Application::GetInfo();
    auto&& appWorkDir = info.GetDefaultAppData();

    auto&& workdir = Utility::GetDefaultDataPath();

    ASSERT_NO_THROW(DBManager::CreateDBLocalJSONReader(appWorkDir));
    ASSERT_NO_THROW(DBManager::CreateDBLocalJSONReader(workdir));

    auto&& reader = DBManager::CreateDBLocalJSONReader(workdir);
    ASSERT_NE(reader, nullptr);
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBaseJSONWriter, Read)
{
    auto&& workdir  = GetDefaultWorkDir();
    auto&& writer   = DBManager::CreateDBLocalJSONWriter(workdir);
    auto&& database = Testing::DBManager::CreateDataBase();
    ASSERT_NO_THROW(writer->Write(*database));

    //////////////////////////////////////////////////////////////////////

    auto&& reader =
        DBManager::CreateDBLocalJSONReader(workdir + '/' + database->GetName());
    ASSERT_NO_THROW(reader->Read());

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBaseJSONWriter, EqualityOfDBStruct)
{
    auto&& workdir  = GetDefaultWorkDir();
    auto&& writer   = DBManager::CreateDBLocalJSONWriter(workdir);
    auto&& database = Testing::DBManager::CreateDataBase();
    ASSERT_NO_THROW(writer->Write(*database));

    //////////////////////////////////////////////////////////////////////

    auto&& reader =
        DBManager::CreateDBLocalJSONReader(workdir + '/' + database->GetName());
    auto&& newdatabase = reader->Read();

    //////////////////////////////////////////////////////////////////////

    EXPECT_EQ(database->GetName(), newdatabase->GetName());
    EXPECT_EQ(database->TablesCount(), newdatabase->TablesCount());

    //////////////////////////////////////////////////////////////////////

    auto&& tablesListOld = database->ListTables();
    auto&& tablesListNew = newdatabase->ListTables();

    ASSERT_NE(tablesListOld, nullptr);
    ASSERT_NE(tablesListNew, nullptr);

    ASSERT_EQ(tablesListOld->size(), tablesListNew->size());
    ASSERT_TRUE(std::equal(tablesListOld->begin(), tablesListOld->end(),
                           tablesListNew->begin()));
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBaseJSONWriter, EqualityOfTablesStruct)
{
    auto&& workdir  = GetDefaultWorkDir();
    auto&& writer   = DBManager::CreateDBLocalJSONWriter(workdir);
    auto&& database = Testing::DBManager::CreateDataBase();
    ASSERT_NO_THROW(writer->Write(*database));

    //////////////////////////////////////////////////////////////////////

    auto&& reader =
        DBManager::CreateDBLocalJSONReader(workdir + '/' + database->GetName());
    auto&& newdatabase = reader->Read();

    //////////////////////////////////////////////////////////////////////

    auto&& tablesListOld = database->ListTables();
    for (auto&& tablename : *tablesListOld)
    {
        auto&& tableold = database->GetTable(tablename);
        auto&& tablenew = newdatabase->GetTable(tablename);

        EXPECT_EQ(tableold.GetName(), tablenew.GetName());
        EXPECT_EQ(tableold.ColumnsCount(), tablenew.ColumnsCount());

        auto&& columnListOld = tableold.ListColumns();
        auto&& columnListNew = tablenew.ListColumns();

        ASSERT_NE(columnListOld, nullptr);
        ASSERT_NE(columnListNew, nullptr);
        ASSERT_EQ(columnListOld->size(), columnListNew->size());
        ASSERT_TRUE(std::equal(columnListOld->begin(), columnListOld->end(),
                               columnListNew->begin()));
    }
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBaseJSONWriter, EqualityOfTablesData)
{
    auto&& workdir  = GetDefaultWorkDir();
    auto&& writer   = DBManager::CreateDBLocalJSONWriter(workdir);
    auto&& database = Testing::DBManager::CreateDataBase();
    ASSERT_NO_THROW(writer->Write(*database));

    //////////////////////////////////////////////////////////////////////

    auto&& reader =
        DBManager::CreateDBLocalJSONReader(workdir + '/' + database->GetName());
    auto&& newdatabase = reader->Read();

    //////////////////////////////////////////////////////////////////////

    auto&& tablesListOld = database->ListTables();
    for (auto&& tablename : *tablesListOld)
    {
        auto&& tableold = database->GetTable(tablename);
        auto&& tablenew = newdatabase->GetTable(tablename);

        auto columnsCount = tableold.ColumnsCount();
        for (int columnIndex = 0; columnIndex < columnsCount; ++columnIndex)
        {
            auto&& columnold = tableold.GetColumn(columnIndex);
            auto&& columnnew = tablenew.GetColumn(columnIndex);

            EXPECT_EQ(columnold.GetName(), columnnew.GetName());
            EXPECT_EQ(columnold.GetSize(), columnnew.GetSize());

            auto rowsCount = columnold.GetSize();
            for (int rowIndex = 0; rowIndex < rowsCount; ++rowIndex)
            {
                auto&& valueold = columnold.GetElement(rowIndex);
                auto&& valuenew = columnold.GetElement(rowIndex);

                EXPECT_TRUE(Interface::AreValuesEqual(valueold, valuenew));
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
