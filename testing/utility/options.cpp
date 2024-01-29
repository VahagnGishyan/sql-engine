
#include <gtest/gtest.h>

#include "test-dir-preparation.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine::Testing;
using namespace SQLEngine::Utility;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(Utility, Options_True)
{
    Option::IOption opTrue{true};
    // Option::ExistOk existokFalse{false};

    EXPECT_TRUE(opTrue);
    EXPECT_EQ(opTrue, true);
    EXPECT_NE(opTrue, false);

    EXPECT_FALSE(!opTrue);
    EXPECT_NE(!opTrue, true);
    EXPECT_EQ(!opTrue, false);
}

TEST(Utility, Options_False)
{
    Option::IOption opTrue{false};
    // Option::ExistOk existokFalse{false};

    EXPECT_FALSE(opTrue);
    EXPECT_EQ(opTrue, false);
    EXPECT_NE(opTrue, true);

    EXPECT_TRUE(!opTrue);
    EXPECT_NE(!opTrue, false);
    EXPECT_EQ(!opTrue, true);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
