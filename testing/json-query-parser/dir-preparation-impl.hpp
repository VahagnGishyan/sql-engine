
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>

#include "interface/i-database.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::JSONQueryParser::Peparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void CreateDatabaseAt(const std::string& path, const std::string& dbName);

    auto CreateInsertIntoQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>;
    auto CreateUpdateQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>;
    auto CreateSelectQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>;
    auto CreateDeleteQueries(const std::string& dir)
        -> std::shared_ptr<std::vector<std::string>>;

    //////////////////////////////////////////////////////////////////////

    void SaveDeleteResultCategories(const std::string& path);
    void SaveDeleteResultTaskcategories(const std::string& path);
    void SaveDeleteResultTasks(const std::string& path);

    void SaveInsertResultCategories(const std::string& path);
    void SaveInsertResultTaskcategories(const std::string& path);
    void SaveInsertResultTasks(const std::string& path);

    void SaveSelectResultCategories(const std::string& path);
    void SaveSelectResultTaskcategories(const std::string& path);
    void SaveSelectResultTasks(const std::string& path);

    void SaveUpdateResultCategories(const std::string& path);
    void SaveUpdateResultTaskcategories(const std::string& path);
    void SaveUpdateResultTasks(const std::string& path);

    //////////////////////////////////////////////////////////////////////

    class IPreparedDir
    {
       public:
        virtual ~IPreparedDir() = default;

       public:
        virtual auto GetEmptyDir() const -> const std::string    = 0;
        virtual auto GetDatabase() const -> Interface::UDataBase = 0;

       public:
        virtual auto GetInsertIntoJSONFileExample() const
            -> const std::string                                           = 0;
        virtual auto GetUpdateJSONFileExample() const -> const std::string = 0;
        virtual auto GetSelectJSONFileExample() const -> const std::string = 0;
        virtual auto GetDeleteJSONFileExample() const -> const std::string = 0;

       public:
        virtual auto GetInsertJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> = 0;
        virtual auto GetUpdateJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> = 0;
        virtual auto GetSelectJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> = 0;
        virtual auto GetDeleteJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> = 0;
    };

    using UPreparedDir = std::unique_ptr<IPreparedDir>;

    auto CreatePreparedDir(const std::string& path) -> UPreparedDir;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Peparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
