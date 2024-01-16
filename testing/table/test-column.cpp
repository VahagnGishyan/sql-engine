
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "table/column.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Column, EmptyCreation)
{
    const std::string name{"empty-column"};
    const Interface::DynamicType type{Interface::DynamicType::Int};

    ASSERT_NO_THROW(SQLEngine::TableNS::Column::Create(name, type));

    auto&& column = SQLEngine::TableNS::Column::Create(name, type);

    EXPECT_NE(column, nullptr);

    EXPECT_EQ(column->GetSize(), 0);
    EXPECT_EQ(column->GetName(), name);
    EXPECT_EQ(column->GetType(), type);
}

//////////////////////////////////////////////////////////////////////////

TEST(Column, AddElement)
{
    const std::string name{"empty-column"};
    const Interface::DynamicType type{Interface::DynamicType::Int};

    auto&& column = SQLEngine::TableNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto&& element = Interface::ColumnE
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Column, EmptyCreation)
{
    const std::string name{"empty-column"};
    const Interface::DynamicType type{Interface::DynamicType::Int};

    ASSERT_NO_THROW(SQLEngine::TableNS::Column::Create(name, type));

    auto&& column = SQLEngine::TableNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);

    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
