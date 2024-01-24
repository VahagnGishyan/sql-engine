
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "database/column-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(ColumnElement, EmptyCreation)
{
    auto&& element = DataBaseNS::ColumnElement::Create();
    ASSERT_NE(element, nullptr);

    EXPECT_TRUE(element->Equal(*element));
    EXPECT_TRUE(element->GreaterThanOrEqualTo(*element));
    EXPECT_TRUE(element->LessThanOrEqualTo(*element));

    EXPECT_FALSE(element->NotEqual(*element));
    EXPECT_FALSE(element->GreaterThan(*element));
    EXPECT_FALSE(element->LessThan(*element));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(ColumnElement, AssignInt)
{
    const int value = 4;

    auto&& element = DataBaseNS::ColumnElement::Create();
    ASSERT_NE(element, nullptr);

    ASSERT_NO_THROW(element->SetValue(value));

    EXPECT_TRUE(element->Equal(value));
    EXPECT_TRUE(element->GreaterThanOrEqualTo(value));
    EXPECT_TRUE(element->LessThanOrEqualTo(value));

    EXPECT_FALSE(element->NotEqual(value));
    EXPECT_FALSE(element->GreaterThan(value));
    EXPECT_FALSE(element->LessThan(value));

    EXPECT_EQ(element->GetValue(), Interface::DynamicValue{value});
}

TEST(ColumnElement, AssignDouble)
{
    const double value = 4.0;

    auto&& element = DataBaseNS::ColumnElement::Create();
    ASSERT_NE(element, nullptr);

    ASSERT_NO_THROW(element->SetValue(value));

    EXPECT_TRUE(element->Equal(value));
    EXPECT_TRUE(element->GreaterThanOrEqualTo(value));
    EXPECT_TRUE(element->LessThanOrEqualTo(value));

    EXPECT_FALSE(element->NotEqual(value));
    EXPECT_FALSE(element->GreaterThan(value));
    EXPECT_FALSE(element->LessThan(value));

    EXPECT_EQ(element->GetValue(), Interface::DynamicValue{value});
}

TEST(ColumnElement, AssignString)
{
    const std::string value = "4.0";

    auto&& element = DataBaseNS::ColumnElement::Create();
    ASSERT_NE(element, nullptr);

    ASSERT_NO_THROW(element->SetValue(value));

    EXPECT_TRUE(element->Equal(value));
    EXPECT_TRUE(element->GreaterThanOrEqualTo(value));
    EXPECT_TRUE(element->LessThanOrEqualTo(value));

    EXPECT_FALSE(element->NotEqual(value));
    EXPECT_FALSE(element->GreaterThan(value));
    EXPECT_FALSE(element->LessThan(value));

    EXPECT_EQ(element->GetValue(), Interface::DynamicValue{value});
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
