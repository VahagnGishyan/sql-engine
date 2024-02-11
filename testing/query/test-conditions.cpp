
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>
#include <gtest/gtest.h>

#include "query/condition.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine::Query;
using namespace SQLEngine::Interface;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, EqualInt)
{
    std::string dummyName = "dummyName";
    int value             = 4;

    auto ucondition = CreateConditionEqual(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test integer equality
    EXPECT_TRUE(condition.Check(CreateUDynValue(4)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(0)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(-1)));
    EXPECT_FALSE(
        condition.Check(CreateUDynValue(std::numeric_limits<int>::max())));
    EXPECT_FALSE(
        condition.Check(CreateUDynValue(std::numeric_limits<int>::min())));
    EXPECT_FALSE(condition.Check(nullptr));
}

TEST(Condition, EqualString)
{
    std::string dummyName = "dummyName";
    std::string value     = "hello";

    auto ucondition = CreateConditionEqual(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test string equality
    EXPECT_TRUE(condition.Check(CreateUDynValue("hello")));
    EXPECT_FALSE(condition.Check(CreateUDynValue("world")));
    EXPECT_FALSE(condition.Check(CreateUDynValue("")));
    EXPECT_FALSE(condition.Check(CreateUDynValue("!@#$%^&*()")));
    EXPECT_FALSE(condition.Check(nullptr));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, EqualNullptrCase)
{
    std::string dummyName = "dummyName";

    auto ucondition = CreateConditionEqual(dummyName, nullptr);
    ASSERT_NE(ucondition, nullptr);
    auto& condition = *ucondition;

    // Test with nullptr
    EXPECT_TRUE(condition.Check(nullptr));

    EXPECT_FALSE(condition.Check(CreateUDynValue(1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(-1)));
    EXPECT_FALSE(
        condition.Check(CreateUDynValue(std::numeric_limits<int>::max())));
    EXPECT_FALSE(
        condition.Check(CreateUDynValue(std::numeric_limits<int>::min())));

    EXPECT_FALSE(condition.Check(CreateUDynValue(3.141)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(3.139)));
    EXPECT_FALSE(
        condition.Check(CreateUDynValue(std::numeric_limits<double>::max())));
    EXPECT_FALSE(
        condition.Check(CreateUDynValue(std::numeric_limits<double>::min())));

    EXPECT_FALSE(condition.Check(CreateUDynValue("world")));
    EXPECT_FALSE(condition.Check(CreateUDynValue("")));
    EXPECT_FALSE(condition.Check(CreateUDynValue("!@#$%^&*()")));
    EXPECT_TRUE(condition.Check(nullptr));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, NotCases)
{
    std::string dummyName = "dummyName";
    int value             = 4;
    auto condEqual = CreateConditionEqual(dummyName, CreateUDynValue(value));

    auto condNotEq = CreateConditionNot(condEqual->Copy());

    EXPECT_TRUE(condEqual->Check(CreateUDynValue(0)) !=
                condNotEq->Check(CreateUDynValue(0)));
    EXPECT_TRUE(condEqual->Check(CreateUDynValue(1)) !=
                condNotEq->Check(CreateUDynValue(1)));
    EXPECT_TRUE(condEqual->Check(CreateUDynValue(2)) !=
                condNotEq->Check(CreateUDynValue(2)));
    EXPECT_TRUE(condEqual->Check(CreateUDynValue(3)) !=
                condNotEq->Check(CreateUDynValue(3)));
    EXPECT_TRUE(condEqual->Check(CreateUDynValue(-3)) !=
                condNotEq->Check(CreateUDynValue(-3)));
    EXPECT_TRUE(condEqual->Check(CreateUDynValue(564564)) !=
                condNotEq->Check(CreateUDynValue(564564)));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, NotEqualInt)
{
    std::string dummyName = "dummyName";
    int value             = 4;

    auto ucondition =
        CreateConditionNotEqual(dummyName, CreateUDynValue(value));

    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test integer inequality
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + 1)));
}

TEST(Condition, NotEqualString)
{
    std::string dummyName = "dummyName";
    std::string value     = "hello";

    auto ucondition =
        CreateConditionNotEqual(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test string inequality
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + " world")));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, GreaterThanInt)
{
    std::string dummyName = "dummyName";
    int value             = 4;

    auto ucondition =
        CreateConditionGreaterThan(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test integer greater than
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + 1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value - 1)));
}

TEST(Condition, GreaterThanDouble)
{
    std::string dummyName = "dummyName";
    double value          = 4.0;

    auto ucondition =
        CreateConditionGreaterThan(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test double greater than
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + 0.1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value - 0.1)));
}

TEST(Condition, GreaterThanString)
{
    std::string dummyName = "dummyName";
    std::string value     = "hello";

    auto ucondition =
        CreateConditionGreaterThan(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test string greater than (based on lexicographical order)
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + " world")));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue("abc")));
}

TEST(Condition, LessThanInt)
{
    std::string dummyName = "dummyName";
    int value             = 4;

    auto ucondition =
        CreateConditionLessThan(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test integer less than
    EXPECT_TRUE(condition.Check(CreateUDynValue(value - 1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value + 1)));
}

TEST(Condition, LessThanDouble)
{
    std::string dummyName = "dummyName";
    double value          = 4.0;

    auto ucondition =
        CreateConditionLessThan(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test double less than
    EXPECT_TRUE(condition.Check(CreateUDynValue(value - 0.1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value + 0.1)));
}

TEST(Condition, LessThanString)
{
    std::string dummyName = "dummyName";
    std::string value     = "hello";

    auto ucondition =
        CreateConditionLessThan(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test string less than (based on lexicographical order)
    EXPECT_TRUE(condition.Check(CreateUDynValue("abc")));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value + " world")));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, GreaterThanOrEqualInt)
{
    std::string dummyName = "dummyName";
    int value             = 4;

    auto ucondition =
        CreateConditionGreaterThanOrEqualTo(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test integer greater than or equal to
    EXPECT_TRUE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value - 1)));
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + 1)));
}

TEST(Condition, GreaterThanOrEqualDouble)
{
    std::string dummyName = "dummyName";
    double value          = 4.0;

    auto ucondition =
        CreateConditionGreaterThanOrEqualTo(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test double greater than or equal to
    EXPECT_TRUE(condition.Check(CreateUDynValue(value + 0.1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value - 0.1)));
}

TEST(Condition, LessThanOrEqualInt)
{
    std::string dummyName = "dummyName";
    int value             = 4;

    auto ucondition =
        CreateConditionLessThanOrEqualTo(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test integer less than or equal to
    EXPECT_TRUE(condition.Check(CreateUDynValue(value - 1)));
    EXPECT_TRUE(condition.Check(CreateUDynValue(value)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value + 1)));
}

TEST(Condition, LessThanOrEqualDouble)
{
    std::string dummyName = "dummyName";
    double value          = 4.0;

    auto ucondition =
        CreateConditionLessThanOrEqualTo(dummyName, CreateUDynValue(value));
    ASSERT_NE(ucondition, nullptr);

    auto& condition = *ucondition;

    // Test double less than or equal to
    EXPECT_TRUE(condition.Check(CreateUDynValue(value - 0.1)));
    EXPECT_FALSE(condition.Check(CreateUDynValue(value + 0.1)));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Condition, AndCases)
{
    std::string dummyName   = "dummyName";
    int intValue            = 4;
    double doubleValue      = 3.14;
    std::string stringValue = "hello";

    // Creating individual conditions
    auto conditionInt =
        CreateConditionLessThan(dummyName, CreateUDynValue(intValue));
    auto conditionDouble =
        CreateConditionGreaterThan(dummyName, CreateUDynValue(doubleValue));
    auto conditionString =
        CreateConditionEqual(dummyName, CreateUDynValue(stringValue));

    // Creating combined conditions using CreateConditionAnd
    auto uconditionAnd1 =
        CreateConditionAnd(conditionInt->Copy(), conditionDouble->Copy());
    auto uconditionAnd2 =
        CreateConditionAnd(conditionDouble->Copy(), conditionString->Copy());

    ASSERT_NE(uconditionAnd1, nullptr);
    ASSERT_NE(uconditionAnd2, nullptr);

    auto& conditionAnd1 = *uconditionAnd1;
    auto& conditionAnd2 = *uconditionAnd2;

    // Test cases for CreateConditionAnd
    EXPECT_FALSE(conditionAnd1.Check(CreateUDynValue(intValue)));
    EXPECT_FALSE(conditionAnd1.Check(CreateUDynValue(doubleValue)));

    EXPECT_FALSE(conditionAnd2.Check(CreateUDynValue(doubleValue)));
    EXPECT_TRUE(conditionAnd2.Check(CreateUDynValue(stringValue)));
}

TEST(Condition, OrCases)
{
    std::string dummyName   = "dummyName";
    int intValue            = 4;
    double doubleValue      = 13.14;
    std::string stringValue = "hello";

    // Creating individual conditions
    auto conditionInt =
        CreateConditionEqual(dummyName, CreateUDynValue(intValue));
    auto conditionDouble =
        CreateConditionGreaterThan(dummyName, CreateUDynValue(doubleValue));
    auto conditionString =
        CreateConditionEqual(dummyName, CreateUDynValue(stringValue));

    // Creating combined conditions using CreateConditionOr
    auto uconditionOr1 =
        CreateConditionOr(conditionInt->Copy(), conditionDouble->Copy());
    auto uconditionOr2 =
        CreateConditionOr(conditionDouble->Copy(), conditionString->Copy());

    ASSERT_NE(uconditionOr1, nullptr);
    ASSERT_NE(uconditionOr2, nullptr);

    auto& conditionOr1 = *uconditionOr1;
    auto& conditionOr2 = *uconditionOr2;

    // Test cases for CreateConditionOr
    EXPECT_TRUE(conditionOr1.Check(CreateUDynValue(intValue)));
    EXPECT_FALSE(conditionOr1.Check(CreateUDynValue(doubleValue)));
    EXPECT_FALSE(conditionOr1.Check(CreateUDynValue(doubleValue - 1)));
    EXPECT_TRUE(conditionOr1.Check(CreateUDynValue(doubleValue + 1)));

    EXPECT_FALSE(conditionOr1.Check(CreateUDynValue(doubleValue)));
    EXPECT_FALSE(conditionOr1.Check(CreateUDynValue(doubleValue - 1)));
    EXPECT_TRUE(conditionOr1.Check(CreateUDynValue(doubleValue + 1)));
    EXPECT_TRUE(conditionOr2.Check(CreateUDynValue(stringValue)));
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
