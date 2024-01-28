
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
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

TEST(RowOrientedTable, Creation)
{
    auto table     = Testing::DataBase::CreateTable();
    auto&& rotable = DataBase::CreateRowOrientedTable(*table);

    //////////////////////////////////////////////////////////////////////

    EXPECT_EQ(rotable->GetTableName(), table->GetName());
    auto columnsInfoList = rotable->GetColumnInfoList();
    ASSERT_EQ(columnsInfoList.size(), table->ColumnsCount());

    //////////////////////////////////////////////////////////////////////

    auto rowsCount = rotable->RowsCount();
    for (auto&& columnsInfo : columnsInfoList)
    {
        ASSERT_TRUE(table->IsColumnExists(columnsInfo.name));
        auto&& column = table->GetColumn(columnsInfo.name);
        EXPECT_EQ(column.GetType(), columnsInfo.type);
        table->GetColumn(columnsInfo.name);
        EXPECT_EQ(column.GetSize(), rowsCount);
    }
}

//////////////////////////////////////////////////////////////////////////

TEST(RowOrientedTable, ListColumnsByName)
{
    auto table     = Testing::DataBase::CreateTable();
    auto&& rotable = DataBase::CreateRowOrientedTable(*table);

    //////////////////////////////////////////////////////////////////////

    EXPECT_EQ(rotable->GetTableName(), table->GetName());
    auto columnsInfoList = rotable->GetColumnInfoList();
    ASSERT_EQ(columnsInfoList.size(), table->ColumnsCount());

    //////////////////////////////////////////////////////////////////////

    for (auto&& columnsInfo : columnsInfoList)
    {
        ASSERT_TRUE(table->IsColumnExists(columnsInfo.name));
        auto&& column = table->GetColumn(columnsInfo.name);
        EXPECT_EQ(column.GetType(), columnsInfo.type);
        table->GetColumn(columnsInfo.name);
    }
}

//////////////////////////////////////////////////////////////////////////

TEST(RowOrientedTable, ColumnsAreNotDuplicated)
{
    auto table     = Testing::DataBase::CreateTable();
    auto&& rotable = DataBase::CreateRowOrientedTable(*table);

    //////////////////////////////////////////////////////////////////////

    EXPECT_EQ(rotable->GetTableName(), table->GetName());
    auto columnsInfoList = rotable->GetColumnInfoList();
    ASSERT_EQ(columnsInfoList.size(), table->ColumnsCount());

    //////////////////////////////////////////////////////////////////////

    const int size = (int)columnsInfoList.size();
    std::vector<int> indexes;
    indexes.resize(size, -1);
    for (auto&& columnsInfo : columnsInfoList)
    {
        auto index = table->GetColumnIndex(columnsInfo.name);
        ASSERT_NE(index, std::nullopt);
        indexes[*index] = *index;
    }

    for (int index = 0; index < size; ++index)
    {
        if (indexes[index] == -1)
        {
            FAIL() << fmt::format(
                "column-index = {} : are not exist in row-oriented-table",
                index);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(RowOrientedTable, EqualityWithTable)
{
    auto table     = Testing::DataBase::CreateTable();
    auto&& roTable = DataBase::CreateRowOrientedTable(*table);

    //////////////////////////////////////////////////////////////////////

    const int columnCount = (int)roTable->GetColumnInfoList().size();
    const int rowCount    = roTable->RowsCount();

    //////////////////////////////////////////////////////////////////////

    for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
    {
        auto&& column = table->GetColumn(columnIndex);
        for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
        {
            auto&& tableValue   = column.GetElement(rowIndex);
            auto&& roTabelValue = roTable->GetValue(rowIndex, columnIndex);
            ASSERT_TRUE(Interface::AreValuesEqual(tableValue, roTabelValue));
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(RowOrientedTable, Copy)
{
    auto table     = Testing::DataBase::CreateTable();
    auto&& roTable = DataBase::CreateRowOrientedTable(*table);

    //////////////////////////////////////////////////////////////////////

    auto&& cpTable = roTable->Copy();

    //////////////////////////////////////////////////////////////////////

    ASSERT_EQ(roTable->GetTableName(), cpTable->GetTableName());
    ASSERT_EQ(roTable->RowsCount(), cpTable->RowsCount());
    ASSERT_EQ(roTable->ColumnsCount(), cpTable->ColumnsCount());

    //////////////////////////////////////////////////////////////////////

    auto&& orColumnInfoList = roTable->GetColumnInfoList();
    auto&& cpColumnInfoList = cpTable->GetColumnInfoList();

    ASSERT_EQ(orColumnInfoList.size(), cpColumnInfoList.size());

    const int columnCount = (int)orColumnInfoList.size();
    for (int index = 0; index < columnCount; ++index)
    {
        auto&& orColumn = orColumnInfoList[index];
        auto&& cpColumn = cpColumnInfoList[index];
        ASSERT_EQ(orColumn.name, cpColumn.name);
        ASSERT_EQ(orColumn.type, cpColumn.type);
    }

    //////////////////////////////////////////////////////////////////////

    const int rowCount = roTable->RowsCount();
    for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
    {
        for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
        {
            auto&& orvalue = roTable->GetValue(rowIndex, columnIndex);
            auto&& cpvalue = cpTable->GetValue(rowIndex, columnIndex);

            if (orvalue == nullptr)
            {
                EXPECT_EQ(cpvalue, nullptr);
            }
            ASSERT_EQ(*orvalue, *cpvalue);
        }
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(RowOrientedTable, CreateTable)
{
    auto inittable  = Testing::DataBase::CreateTable();
    auto&& roTable  = DataBase::CreateRowOrientedTable(*inittable);
    auto&& newTable = roTable->CreateTable();

    //////////////////////////////////////////////////////////////////////

    const int columnCount = (int)roTable->GetColumnInfoList().size();
    const int rowCount    = roTable->RowsCount();

    EXPECT_EQ(roTable->GetTableName(), newTable->GetName());
    auto columnsInfoList = roTable->GetColumnInfoList();
    ASSERT_EQ(columnsInfoList.size(), newTable->ColumnsCount());

    ////////////////////////////////////////////////////////////////////

    auto rowsCount = roTable->RowsCount();
    for (auto&& columnsInfo : columnsInfoList)
    {
        ASSERT_TRUE(newTable->IsColumnExists(columnsInfo.name));
        auto&& column = newTable->GetColumn(columnsInfo.name);
        EXPECT_EQ(column.GetType(), columnsInfo.type);
        newTable->GetColumn(columnsInfo.name);
        EXPECT_EQ(column.GetSize(), rowsCount);
    }

    ////////////////////////////////////////////////////////////////////

    for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
    {
        auto&& column = newTable->GetColumn(columnIndex);
        for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
        {
            auto&& tableValue   = column.GetElement(rowIndex);
            auto&& roTabelValue = roTable->GetValue(rowIndex, columnIndex);
            ASSERT_TRUE(Interface::AreValuesEqual(tableValue, roTabelValue));
        }
    }

    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
