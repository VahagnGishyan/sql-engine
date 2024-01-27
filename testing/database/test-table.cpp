
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "database/database.hpp"
#include "utility.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Table, EmptyCreation)
{
    const std::string name{"test-table"};

    auto&& table = DataBase::CreateTable(name);

    EXPECT_EQ(name, table->GetName());
    EXPECT_EQ(0, table->ColumnsCount());
    EXPECT_EQ(0, table->ListColumns()->size());
}

//////////////////////////////////////////////////////////////////////////

TEST(Table, SetNameAndGetSetName)
{
    const std::string initialName{"initial-name"};
    const std::string newName{"new-name"};
    auto&& table = DataBase::CreateTable(initialName);
    EXPECT_EQ(initialName, table->GetName());
    table->SetName(newName);
    EXPECT_EQ(newName, table->GetName());
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Table, ColumnManipulation)
{
    // Arrange
    const std::string tableName{"test-table"};
    auto&& table = DataBase::CreateTable(tableName);

    // Act: Add columns
    auto&& column1 =
        DataBase::CreateColumn("Column1", Interface::DynamicType::Int);
    auto&& column2 =
        DataBase::CreateColumn("Column2", Interface::DynamicType::Int);

    table->AddColumn(std::move(column1));
    table->AddColumn(std::move(column2));

    // Assert: List columns and check count
    auto columnsList = table->ListColumns();
    ASSERT_EQ(table->ColumnsCount(), 2);
    ASSERT_EQ(table->ColumnsCount(), columnsList->size());
    EXPECT_EQ((*columnsList)[0], "Column1");
    EXPECT_EQ((*columnsList)[1], "Column2");

    // Act: Remove a column
    bool removed = table->RemoveColumn("Column1");

    // Assert: Check column removal and count
    ASSERT_TRUE(removed);
    columnsList = table->ListColumns();
    ASSERT_EQ(1, columnsList->size());
    ASSERT_EQ(table->ColumnsCount(), columnsList->size());
    EXPECT_EQ("Column2", (*columnsList)[0]);

    // Act: Rename a column
    table->RenameColumn("Column2", "NewColumn");

    // Assert: Check column renaming
    columnsList = table->ListColumns();
    EXPECT_EQ(1, columnsList->size());
    EXPECT_EQ("NewColumn", (*columnsList)[0]);

    // Assert: Check column count
    EXPECT_EQ(table->ColumnsCount(), 1);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Table, NotEmptyColumns)
{
    auto&& column0 = Testing::DataBase::CreateIntColumn();
    auto&& column1 = Testing::DataBase::CreateDoubleColumn();
    auto&& column2 = Testing::DataBase::CreateStringColumn();

    //////////////////////////////////////////////////////////////////////

    const std::string tablename{"test-table"};

    auto&& table = DataBase::CreateTable(tablename);

    table->AddColumn(column0->Copy());
    table->AddColumn(column1->Copy());
    table->AddColumn(column2->Copy());

    //////////////////////////////////////////////////////////////////////

    ASSERT_EQ(table->ColumnsCount(), 3);

    EXPECT_EQ(table->GetColumn(0).GetName(), column0->GetName());
    EXPECT_EQ(table->GetColumn(0).GetSize(), column0->GetSize());

    EXPECT_EQ(table->GetColumn(1).GetName(), column1->GetName());
    EXPECT_EQ(table->GetColumn(1).GetSize(), column1->GetSize());

    EXPECT_EQ(table->GetColumn(2).GetName(), column2->GetName());
    EXPECT_EQ(table->GetColumn(2).GetSize(), column2->GetSize());
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Table, GetColumnIndex)
{
    auto&& column0 = Testing::DataBase::CreateIntColumn();
    auto&& column1 = Testing::DataBase::CreateDoubleColumn();
    auto&& column2 = Testing::DataBase::CreateStringColumn();

    //////////////////////////////////////////////////////////////////////

    const std::string tablename{"test-table"};

    auto&& table = DataBase::CreateTable(tablename);

    table->AddColumn(column0->Copy());
    table->AddColumn(column1->Copy());
    table->AddColumn(column2->Copy());

    //////////////////////////////////////////////////////////////////////

    auto opResult0 = table->GetColumnIndex(column0->GetName());
    auto opResult1 = table->GetColumnIndex(column1->GetName());
    auto opResult2 = table->GetColumnIndex(column2->GetName());

    ASSERT_NE(opResult0, std::nullopt);
    ASSERT_NE(opResult1, std::nullopt);
    ASSERT_NE(opResult2, std::nullopt);

    auto index0 = *opResult0;
    auto index1 = *opResult1;
    auto index2 = *opResult2;

    //////////////////////////////////////////////////////////////////////

    EXPECT_EQ(table->GetColumn(index0).GetName(), column0->GetName());
    EXPECT_EQ(table->GetColumn(index1).GetName(), column1->GetName());
    EXPECT_EQ(table->GetColumn(index2).GetName(), column2->GetName());
}

TEST(Table, GetColumn)
{
    auto&& column0 = Testing::DataBase::CreateIntColumn();
    auto&& column1 = Testing::DataBase::CreateDoubleColumn();
    auto&& column2 = Testing::DataBase::CreateStringColumn();

    //////////////////////////////////////////////////////////////////////

    const std::string tablename{"test-table"};

    auto&& table = DataBase::CreateTable(tablename);

    table->AddColumn(column0->Copy());
    table->AddColumn(column1->Copy());
    table->AddColumn(column2->Copy());

    ////////////////////////////////////////////////////////////////////

    // Act and Assert: Check valid column retrieval by name
    auto&& retrievedColumnInt    = table->GetColumn(column0->GetName());
    auto&& retrievedColumnDouble = table->GetColumn(column1->GetName());
    auto&& retrievedColumnString = table->GetColumn(column2->GetName());

    EXPECT_EQ(retrievedColumnInt.GetName(), column0->GetName());
    EXPECT_EQ(retrievedColumnDouble.GetName(), column1->GetName());
    EXPECT_EQ(retrievedColumnString.GetName(), column2->GetName());

    // Act and Assert: Check invalid column retrieval by name (using try-catch
    // to check for exception)
    try
    {
        auto&& nonexistentColumn = table->GetColumn("NonexistentColumn");
        // If we reach this point, it means an exception was not thrown, which
        // is unexpected
        FAIL() << "Expected an exception for accessing a nonexistent column, "
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

TEST(Table, ListColumns)
{
    auto&& column0 = Testing::DataBase::CreateIntColumn();
    auto&& column1 = Testing::DataBase::CreateDoubleColumn();
    auto&& column2 = Testing::DataBase::CreateStringColumn();

    //////////////////////////////////////////////////////////////////////

    const std::string tablename{"test-table"};

    auto&& table = DataBase::CreateTable(tablename);

    table->AddColumn(column0->Copy());
    table->AddColumn(column1->Copy());
    table->AddColumn(column2->Copy());

    ////////////////////////////////////////////////////////////////////

    auto&& columnList = table->ListColumns();

    for (auto&& columnName : *columnList)
    {
        auto opIndex = table->GetColumnIndex(columnName);

        ASSERT_NE(opIndex, std::nullopt);
        auto index = *opIndex;

        EXPECT_EQ(table->GetColumn(index).GetName(), columnName);
        EXPECT_EQ(table->GetColumn(columnName).GetName(), columnName);
    }
}

//////////////////////////////////////////////////////////////////////////

TEST(Table, IsColumnExists)
{
    auto&& table = Testing::DataBase ::CreateTable();

    //////////////////////////////////////////////////////////////////////

    auto&& columnsList = table->ListColumns();

    for (auto&& columnName : *columnsList)
    {
        EXPECT_EQ(table->GetColumn(columnName).GetName(), columnName);
        EXPECT_TRUE(table->IsColumnExists(columnName));
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Table, CopyWithNewName)
{
    auto&& column0 = Testing::DataBase::CreateIntColumn();
    auto&& column1 = Testing::DataBase::CreateDoubleColumn();
    auto&& column2 = Testing::DataBase::CreateStringColumn();

    //////////////////////////////////////////////////////////////////////

    const std::string tableName{"test-table"};

    auto&& table = DataBase::CreateTable(tableName);

    table->AddColumn(column0->Copy());
    table->AddColumn(column1->Copy());
    table->AddColumn(column2->Copy());

    //////////////////////////////////////////////////////////////////////

    const std::string newTableName{"new-test-table"};
    auto&& newtable = table->Copy(newTableName);

    EXPECT_EQ(table->GetName(), tableName);
    EXPECT_EQ(newtable->GetName(), newTableName);

    auto&& columnListOld = table->ListColumns();
    auto&& columnListNew = newtable->ListColumns();

    ASSERT_NE(columnListOld, nullptr);
    ASSERT_NE(columnListNew, nullptr);
    ASSERT_EQ(columnListOld->size(), columnListNew->size());
    ASSERT_TRUE(std::equal(columnListOld->begin(), columnListOld->end(),
                           columnListNew->begin()));

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////

TEST(Table, CopyWithOutNewName)
{
    auto&& column0 = Testing::DataBase::CreateIntColumn();
    auto&& column1 = Testing::DataBase::CreateDoubleColumn();
    auto&& column2 = Testing::DataBase::CreateStringColumn();

    //////////////////////////////////////////////////////////////////////

    const std::string tableName{"test-table"};

    auto&& table = DataBase::CreateTable(tableName);

    table->AddColumn(column0->Copy());
    table->AddColumn(column1->Copy());
    table->AddColumn(column2->Copy());

    //////////////////////////////////////////////////////////////////////

    auto&& newtable = table->Copy();

    EXPECT_EQ(table->GetName(), newtable->GetName());

    auto&& columnListOld = table->ListColumns();
    auto&& columnListNew = newtable->ListColumns();

    ASSERT_NE(columnListOld, nullptr);
    ASSERT_NE(columnListNew, nullptr);
    ASSERT_EQ(columnListOld->size(), columnListNew->size());
    ASSERT_TRUE(std::equal(columnListOld->begin(), columnListOld->end(),
                           columnListNew->begin()));

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
