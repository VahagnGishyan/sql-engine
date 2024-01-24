
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "database/column-element.hpp"
#include "database/column.hpp"

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

    ASSERT_NO_THROW(SQLEngine::DataBaseNS::Column::Create(name, type));

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    EXPECT_NE(column, nullptr);

    EXPECT_EQ(column->GetSize(), 0);
    EXPECT_EQ(column->GetName(), name);
    EXPECT_EQ(column->GetType(), type);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Column, AddElementInt)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Int};
    const Interface::GetDynamicType<type>::type value = 4;

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto dynvalue = Interface::DynamicValue{};
    dynvalue      = value;

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 1);
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 5);
}

//////////////////////////////////////////////////////////////////////////

TEST(Column, AddElementDouble)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Double};
    const Interface::GetDynamicType<type>::type value = 4.4;

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto dynvalue = Interface::DynamicValue{};
    dynvalue      = value;

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 1);
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 5);
}

//////////////////////////////////////////////////////////////////////////

TEST(Column, AddElementString)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::String};
    const Interface::GetDynamicType<type>::type value = "4.4";

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto dynvalue = Interface::DynamicValue{};
    dynvalue      = value;

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 1);
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));
    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 5);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Column, TypeIntAddWrongElements)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Int};

    const Interface::GetDynamicType<type>::type value = 4;

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto dynvalue = Interface::DynamicValue{};
    dynvalue      = value;

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 1);
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);

    dynvalue = 4.4;
    EXPECT_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)),
        std::exception);
    dynvalue = "4.4";
    EXPECT_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)),
        std::exception);

    ASSERT_EQ(column->GetSize(), 1);
    dynvalue = value;
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);
}

//////////////////////////////////////////////////////////////////////////

TEST(Column, TypeDoubleAddWrongElements)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Double};

    const Interface::GetDynamicType<type>::type value = 4.4;

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto dynvalue = Interface::DynamicValue{};
    dynvalue      = value;

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 1);
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);

    dynvalue = 4;
    EXPECT_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)),
        std::exception);
    dynvalue = "4.4";
    EXPECT_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)),
        std::exception);

    ASSERT_EQ(column->GetSize(), 1);
    dynvalue = value;
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);
}

//////////////////////////////////////////////////////////////////////////

TEST(Column, TypeStringAddWrongElements)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::String};

    const Interface::GetDynamicType<type>::type value = "4.4";

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetSize(), 0);
    ASSERT_EQ(column->GetName(), name);
    ASSERT_EQ(column->GetType(), type);

    auto dynvalue = Interface::DynamicValue{};
    dynvalue      = value;

    ASSERT_NO_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)));

    ASSERT_EQ(column->GetSize(), 1);
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);

    dynvalue = 4;
    EXPECT_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)),
        std::exception);
    dynvalue = 4.4;
    EXPECT_THROW(
        column->AddElement(DataBaseNS::ColumnElement::Create(dynvalue)),
        std::exception);

    ASSERT_EQ(column->GetSize(), 1);
    dynvalue = value;
    ASSERT_EQ(column->GetElement(0).GetValue(), dynvalue);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Column, GetIntElement)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Int};
    auto elements = std::vector<Interface::GetDynamicType<type>::type>{
        0, 41, 874456465, 65465, 485485485, -548548, 48548, -121};
    auto size = elements.size();

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    for (auto element : elements)
    {
        column->AddElement(DataBaseNS::ColumnElement::Create(element));
    }

    ASSERT_EQ(column->GetSize(), size);

    auto dynvalue = Interface::DynamicValue{};
    for (int index = 0; index < size; ++index)
    {
        dynvalue = elements[index];
        ASSERT_EQ(column->GetElement(index).GetValue(), dynvalue);
    }
}
//////////////////////////////////////////////////////////////////////////

TEST(Column, GetDoubleElement)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Double};
    auto elements = std::vector<Interface::GetDynamicType<type>::type>{
        0.45, 41.5, 87445646.5, 65.465, 48548.5485, -5485.48, 48.548, -12.1};
    auto size = elements.size();

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    for (auto element : elements)
    {
        column->AddElement(DataBaseNS::ColumnElement::Create(element));
    }

    ASSERT_EQ(column->GetSize(), size);

    auto dynvalue = Interface::DynamicValue{};
    for (int index = 0; index < size; ++index)
    {
        dynvalue = elements[index];
        ASSERT_EQ(column->GetElement(index).GetValue(), dynvalue);
    }
}
//////////////////////////////////////////////////////////////////////////

TEST(Column, GetStringElement)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::String};
    auto elements = std::vector<Interface::GetDynamicType<type>::type>{
        "0",          "41",         ",",
        "",           "uijfhbuieu", "uifhdg3uyhhd3478dyhsb$%$^&*",
        " 874456465", "    ",
    };
    auto size = elements.size();

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    for (auto element : elements)
    {
        column->AddElement(DataBaseNS::ColumnElement::Create(element));
    }

    ASSERT_EQ(column->GetSize(), size);

    auto dynvalue = Interface::DynamicValue{};
    for (int index = 0; index < size; ++index)
    {
        dynvalue = elements[index];
        ASSERT_EQ(column->GetElement(index).GetValue(), dynvalue);
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Column, CopyTypeInt)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Int};
    auto elements = std::vector<Interface::GetDynamicType<type>::type>{
        0, 41, 874456465, 65465, 485485485, -548548, 48548, -121};
    auto size = elements.size();

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    for (auto element : elements)
    {
        column->AddElement(DataBaseNS::ColumnElement::Create(element));
    }
    auto&& newcolumn = column->Copy("new-empty-column");

    for (int index = 0; index < size; ++index)
    {
        ASSERT_EQ(column->GetElement(index).GetValue(),
                  newcolumn->GetElement(index).GetValue());
    }
}
//////////////////////////////////////////////////////////////////////////

TEST(Column, CopyTypeDouble)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::Double};
    auto elements = std::vector<Interface::GetDynamicType<type>::type>{
        0.45, 41.5, 87445646.5, 65.465, 48548.5485, -5485.48, 48.548, -12.1};
    auto size = elements.size();

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    for (auto element : elements)
    {
        column->AddElement(DataBaseNS::ColumnElement::Create(element));
    }
    auto&& newcolumn = column->Copy("new-empty-column");

    for (int index = 0; index < size; ++index)
    {
        ASSERT_EQ(column->GetElement(index).GetValue(),
                  newcolumn->GetElement(index).GetValue());
    }
}
//////////////////////////////////////////////////////////////////////////

TEST(Column, CopyTypeString)
{
    const std::string name{"empty-column"};
    constexpr Interface::DynamicType type{Interface::DynamicType::String};
    auto elements = std::vector<Interface::GetDynamicType<type>::type>{
        "0",          "41",         ",",
        "",           "uijfhbuieu", "uifhdg3uyhhd3478dyhsb$%$^&*",
        " 874456465", "    ",
    };
    auto size = elements.size();

    auto&& column = SQLEngine::DataBaseNS::Column::Create(name, type);

    for (auto element : elements)
    {
        column->AddElement(DataBaseNS::ColumnElement::Create(element));
    }
    auto&& newcolumn = column->Copy("new-empty-column");

    for (int index = 0; index < size; ++index)
    {
        ASSERT_EQ(column->GetElement(index).GetValue(),
                  newcolumn->GetElement(index).GetValue());
    }
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
