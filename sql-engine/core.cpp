
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "core.hpp"

#include "logging/logging.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class EngineWrapper
    {
       public:
        static bool IsInitialized()
        {
            return (s_engine != nullptr);
        }

       public:
        static void AssertInitialized()
        {
            Utility::Assert(EngineWrapper::IsInitialized() == false,
                            "SQLEngine::EngineWrapper::AssertInitialized(), engine is already initialized.");
        }
        static void AssertNoneInitialized()
        {
            Utility::Assert(EngineWrapper::IsInitialized() == true,
                            "SQLEngine::EngineWrapper::AssertNoneInitialized(), engine is not initialized.");
        }

       public:
        static void Init(UEngine engine)
        {
            AssertNoneInitialized();
            s_engine = std::move(engine);
        }

       public:
        static auto GetEngine() -> Engine&
        {
            AssertInitialized();
            return *s_engine;
        }

       protected:
        static UEngine s_engine;
    };

    UEngine EngineWrapper::s_engine = nullptr;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void Init(UEngine engine)
    {
        EngineWrapper::Init(std::move(engine));
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool DatabaseExists(const std::string& name)
    {
        auto&& engine = EngineWrapper::GetEngine();
        return engine.DatabaseExists(name);
    }

    auto ListDatabases() -> DataBaseNameList
    {
        auto&& engine = EngineWrapper::GetEngine();
        return std::move(engine.ListDatabases());
    }

    auto ListConnectedDatabases() -> DataBaseNameList
    {
        auto&& engine = EngineWrapper::GetEngine();
        return std::move(engine.ListConnectedDatabases());
    }

    //////////////////////////////////////////////////////////////////////

    auto CreateDatabase(const std::string& name) -> WDataBase
    {
        auto&& engine = EngineWrapper::GetEngine();
        return engine.CreateDatabase(name);
    }
    void DropDatabase(const std::string& name)
    {
        auto&& engine = EngineWrapper::GetEngine();
        engine.DropDatabase(name);
    }

    //////////////////////////////////////////////////////////////////////

    auto ConnectDatabase(const std::string& name) -> WDataBase
    {
        auto&& engine = EngineWrapper::GetEngine();
        return engine.ConnectDatabase(name);
    }
    void DisconnectDatabase(const std::string& name)
    {
        auto&& engine = EngineWrapper::GetEngine();
        engine.DropDatabase(name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
