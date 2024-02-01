
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

#include "local-database/local-database.hpp"
#include "utility.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

using namespace SQLEngine;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, Init)
{
    ASSERT_NO_THROW(Testing::LocalDataBase::GetDefaultTestDir());
    auto&& testdir = Testing::LocalDataBase::GetDefaultTestDir();
    auto&& dbdir   = testdir + "/my-db";
    ASSERT_NO_THROW(LocalDataBase::Init(dbdir));
}

////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, InvalidInit)
{
    // std::string nonexitingPath = "";
    // ASSERT_THROW(LocalDataBase::Init(nonexitingPath),
    //              std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
