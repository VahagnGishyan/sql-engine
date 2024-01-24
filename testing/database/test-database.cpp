
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "database/column-element.hpp"
#include "database/database.hpp"
#include "database/table.hpp"
#include "utility.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBase, EmptyCreation)
{
    const std::string name{"test-database"};

    auto&& database = DataBase::Create(name);

    EXPECT_EQ(name, database->GetName());
    EXPECT_EQ(0, database->TablesCount());
    EXPECT_EQ(0, database->ListTables()->size());
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBase, SetNameAndGetSetName)
{
    const std::string initialName{"initial-name"};
    const std::string newName{"new-name"};
    auto&& database = DataBase::Create(initialName);
    EXPECT_EQ(initialName, database->GetName());
    database->SetName(newName);
    EXPECT_EQ(newName, database->GetName());
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBase, AddTables)
{
    // Arrange
    const std::string databaseName{"test-table"};
    auto&& database = DataBase::Create(databaseName);

    // Act: Add columns
    auto tableName1 = std::string{"empty-table-1"};
    auto tableName2 = std::string{"empty-table-2"};
    auto&& table1   = Table::Create(tableName1);
    auto&& table2   = Table::Create(tableName2);

    //////////////////////////////////////////////////////////////////////

    database->AddTable(table1->Copy());
    database->AddTable(table2->Copy());

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBase, RemoveTable)
{
    // Arrange
    const std::string databaseName{"test-table"};
    auto&& database = DataBase::Create(databaseName);

    // Act: Add columns
    auto tableName1 = std::string{"empty-table-1"};
    auto tableName2 = std::string{"empty-table-2"};
    auto&& table1   = Table::Create(tableName1);
    auto&& table2   = Table::Create(tableName2);

    database->AddTable(table1->Copy());
    database->AddTable(table2->Copy());

    //////////////////////////////////////////////////////////////////////

    // Act: Remove a table
    ASSERT_NO_THROW(database->RemoveTable(tableName1));

    // Assert: Check table removal and count
    auto tablesList = database->ListTables();
    ASSERT_EQ(1, tablesList->size());
    ASSERT_EQ(database->TablesCount(), tablesList->size());
    EXPECT_EQ(tableName2, (*tablesList)[0]);
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBase, RenameTable)
{
    // Arrange
    const std::string databaseName{"test-table"};
    auto&& database = DataBase::Create(databaseName);

    // Act: Add columns
    auto tableName1 = std::string{"empty-table-1"};
    auto tableName2 = std::string{"empty-table-2"};
    auto&& table1   = Table::Create(tableName1);
    auto&& table2   = Table::Create(tableName2);

    database->AddTable(table1->Copy());
    database->AddTable(table2->Copy());

    //////////////////////////////////////////////////////////////////////

    // Act: Rename a table
    auto tableNewName = std::string{"new-empty-table"};
    database->RenameTable(tableName1, tableNewName);

    // Assert: Check table renaming
    auto tablesList = database->ListTables();
    EXPECT_EQ(2, tablesList->size());
    EXPECT_EQ(tableNewName, (*tablesList)[0]);

    // Assert: Check table count
    EXPECT_EQ(database->TablesCount(), 2);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBase, NotEmptyTables)
{
    const std::string databaseName{"test-table"};
    auto&& database = DataBase::Create(databaseName);

    //////////////////////////////////////////////////////////////////////

    auto tables = Testing::DataBase::CreateListOfTables();

    for (auto&& table : *tables)
    {
        database->AddTable(table->Copy());
    }

    ASSERT_EQ(database->TablesCount(), tables->size());
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBase, GetTable)
{
    const std::string databaseName{"test-table"};
    auto&& database = DataBase::Create(databaseName);

    //////////////////////////////////////////////////////////////////////

    auto tables = Testing::DataBase::CreateListOfTables();

    for (auto&& table : *tables)
    {
        database->AddTable(table->Copy());
    }

    //////////////////////////////////////////////////////////////////////

    ASSERT_EQ(database->TablesCount(), tables->size());

    for (auto&& table : *tables)
    {
        auto&& retrievedTable = database->GetTable(table->GetName());
        EXPECT_EQ(retrievedTable.GetName(), table->GetName());
    }

    //////////////////////////////////////////////////////////////////////

    // Act and Assert: Check invalid column retrieval by name (using try-catch
    // to check for exception)
    try
    {
        auto&& nonexistentColumn = database->GetTable("NonexistentTable");
        // If we reach this point, it means an exception was not thrown, which
        // is unexpected
        FAIL() << "Expected an exception for accessing a nonexistent table, "
                  "but none was thrown.";
    }
    catch (const std::exception& e)
    {
        // Expected exception for accessing a nonexistent column
        SUCCEED();
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBase, ListTables)
{
    auto database = Testing::DataBase::CreateDataBase();

    //////////////////////////////////////////////////////////////////////

    auto&& tablesList = database->ListTables();

    for (auto&& tableName : *tablesList)
    {
        EXPECT_EQ(database->GetTable(tableName).GetName(), tableName);
        EXPECT_TRUE(database->IsTableExists(tableName));
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(DataBase, CopyWithNewName)
{
    auto database = Testing::DataBase::CreateDataBase();

    //////////////////////////////////////////////////////////////////////

    const std::string newTableName{"new-test-table"};
    auto&& newtable = database->Copy(newTableName);

    EXPECT_EQ(newtable->GetName(), newTableName);
    EXPECT_EQ(newtable->TablesCount(), database->TablesCount());
    EXPECT_EQ(newtable->ListTables()->size(), database->ListTables()->size());
    EXPECT_NE(newtable->GetName(), database->GetName());

    auto&& tablesListOld = database->ListTables();
    auto&& tablesListNew = newtable->ListTables();

    ASSERT_NE(tablesListOld, nullptr);
    ASSERT_NE(tablesListNew, nullptr);
    ASSERT_EQ(tablesListOld->size(), tablesListNew->size());
    ASSERT_TRUE(std::equal(tablesListOld->begin(), tablesListOld->end(),
                           tablesListNew->begin()));

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST(DataBase, CopyWithOutNewName)
{
    auto database = Testing::DataBase::CreateDataBase();

    //////////////////////////////////////////////////////////////////////

    auto&& newtable = database->Copy();

    EXPECT_EQ(database->GetName(), newtable->GetName());

    auto&& tablesListOld = database->ListTables();
    auto&& tablesListNew = newtable->ListTables();

    ASSERT_NE(tablesListOld, nullptr);
    ASSERT_NE(tablesListNew, nullptr);
    ASSERT_EQ(tablesListOld->size(), tablesListNew->size());
    ASSERT_TRUE(std::equal(tablesListOld->begin(), tablesListOld->end(),
                           tablesListNew->begin()));

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
