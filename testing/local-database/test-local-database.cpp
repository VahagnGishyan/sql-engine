
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

    LocalDataBase::Drop(dbdir);
}

////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, NonexitingPath)
{
    std::string nonexitingPath = "";
    ASSERT_THROW(LocalDataBase::Init(nonexitingPath), std::exception);
}

////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, ExitingDataBasePath)
{
    ASSERT_NO_THROW(Testing::LocalDataBase::GetDefaultTestDir());
    auto&& testdir = Testing::LocalDataBase::GetDefaultTestDir();

    auto&& dbdir = testdir + "/my-db";
    ASSERT_NO_THROW(LocalDataBase::Init(dbdir));

    ASSERT_THROW(LocalDataBase::Init(dbdir), std::exception);

    LocalDataBase::Drop(dbdir);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, Connect)
{
    ASSERT_NO_THROW(Testing::LocalDataBase::GetDefaultTestDir());
    auto&& testdir = Testing::LocalDataBase::GetDefaultTestDir();

    auto&& dbdir = testdir + "/test-connection/my-db";
    ASSERT_NO_THROW(LocalDataBase::Init(dbdir));

    ASSERT_NO_THROW(LocalDataBase::Connect(dbdir));
    ASSERT_NO_THROW(LocalDataBase::Connect(dbdir));

    auto&& db = LocalDataBase::Connect(dbdir);
    ASSERT_NE(db, nullptr);

    db->Drop();
}

//////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, GeneralMethodsOfConnection)
{
    ASSERT_NO_THROW(Testing::LocalDataBase::GetDefaultTestDir());
    auto&& testdir = Testing::LocalDataBase::GetDefaultTestDir();

    auto&& dbdir = testdir + "/test-connection/my-db";
    ASSERT_NO_THROW(LocalDataBase::Init(dbdir));

    ASSERT_NO_THROW(LocalDataBase::Connect(dbdir));
    ASSERT_NO_THROW(LocalDataBase::Connect(dbdir));

    auto&& db = LocalDataBase::Connect(dbdir);
    ASSERT_NE(db, nullptr);
    ASSERT_NO_THROW(LocalDataBase::Disconnect(*db));
    ASSERT_NE(db, nullptr);

    db = LocalDataBase::Connect(dbdir);
    ASSERT_NE(db, nullptr);
    ASSERT_NO_THROW(LocalDataBase::Disconnect(*db));
    ASSERT_NE(db, nullptr);
}

//////////////////////////////////////////////////////////////////////////

TEST(LocalDataBase, MethodsOfConnection)
{
    ASSERT_NO_THROW(Testing::LocalDataBase::GetDefaultTestDir());
    auto&& testdir = Testing::LocalDataBase::GetDefaultTestDir();

    auto&& dbdir = testdir + "/test-connection/my-db";
    ASSERT_NO_THROW(LocalDataBase::Init(dbdir));

    auto&& db = LocalDataBase::Connect(dbdir);
    ASSERT_NE(db, nullptr);
    ASSERT_THROW(db->Connect(dbdir), std::exception);
    ASSERT_NO_THROW(LocalDataBase::Disconnect(*db));
    ASSERT_NO_THROW(db->Connect(dbdir));
    ASSERT_THROW(db->Connect(dbdir), std::exception);
    ASSERT_NO_THROW(db->Disconnect(dbdir));

    db->Connect(dbdir);
    ASSERT_NE(db, nullptr);
    ASSERT_NO_THROW(db->Disconnect());
    ASSERT_THROW(db->Disconnect(), std::exception);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
