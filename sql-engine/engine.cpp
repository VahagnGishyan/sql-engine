
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "engine.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool Engine::DatabaseExists(const std::string& name)
    {
        Interface::NotImplYet("engine.cpp, Engine::DatabaseExists()");
        return false;
    }
    auto Engine::ListDatabases() -> DataBaseNameList
    {
        Interface::NotImplYet("engine.cpp, Engine::ListDatabases()");
        return DataBaseNameList{};
    }
    auto Engine::ListConnectedDatabases() -> DataBaseNameList
    {
        Interface::NotImplYet("engine.cpp, Engine::ListConnectedDatabases()");
        return DataBaseNameList{};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Engine::CreateDatabase(const std::string& name) -> WDataBase
    {
        Interface::NotImplYet("engine.cpp, Engine::CreateDatabase()");
        return WDataBase{};
    }
    void Engine::DropDatabase(const std::string& name)
    {
        Interface::NotImplYet("engine.cpp, Engine::DropDatabase()");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Engine::ConnectDatabase(const std::string& name) -> WDataBase
    {
        Interface::NotImplYet("engine.cpp, Engine::ConnectDatabase()");
    }
    void Engine::DisconnectDatabase(const std::string& name)
    {
        Interface::NotImplYet("engine.cpp, Engine::DisconnectDatabase()");
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
