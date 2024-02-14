
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

#include "database/database.hpp"
#include "dir-preparation-impl.hpp"
#include "dir-preparation.hpp"
#include "local-database/db-local-json-stream.hpp"
#include "testing/json-query-parser/dir-preparation.hpp"
#include "utility/core.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::JSONQueryParser::Preparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PreparedDir;
    void InitJSONQueryWorkDirAt(const PreparedDir& dir);

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PreparedDir : public IPreparedDir
    {
       public:
        PreparedDir(const std::string& path) : m_path{path}
        {
            InitJSONQueryWorkDir(*this);
        }

       public:
        auto GetEmptyDir() const -> const std::string override
        {
            std::string path = fmt::format("{}/empty-dir", m_path);
            return path;
        }
        auto GetResultDir() const -> const std::string override
        {
            return fmt::format("{}/result-dir", m_path);
        }

       public:
        auto GetDatabase() const -> Interface::UDataBase
        {
            auto dbdir  = GetDataBaseDir();
            auto reader = LocalDataBase::CreateDBLocalJSONReader(dbdir);
            return reader->Read();
        }

       public:
        auto GetInsertIntoJSONFileExample() const -> const std::string override
        {
            return (*m_insertIntoPaths).at(0);
        }
        auto GetUpdateJSONFileExample() const -> const std::string override
        {
            return (*m_updatePaths).at(0);
        }
        auto GetSelectJSONFileExample() const -> const std::string override
        {
            return (*m_selectPaths).at(0);
        }
        auto GetDeleteJSONFileExample() const -> const std::string override
        {
            return (*m_deletePaths).at(0);
        }

       public:
        auto GetInsertJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> override
        {
            return m_insertIntoPaths;
        }
        auto GetUpdateJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> override
        {
            return m_updatePaths;
        }
        auto GetSelectJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> override
        {
            return m_selectPaths;
        }
        auto GetDeleteJSONExamples() const
            -> const std::shared_ptr<std::vector<std::string>> override
        {
            return m_deletePaths;
        }

       protected:
        auto GetInsertIntoDir() const -> const std::string
        {
            return fmt::format("{}/insert-into-dir", m_path);
        }
        auto GetSelectDir() const -> const std::string
        {
            return fmt::format("{}/select-dir", m_path);
        }
        auto GetDeleteDir() const -> const std::string
        {
            return fmt::format("{}/delete-dir", m_path);
        }
        auto GetUpdateDir() const -> const std::string
        {
            return fmt::format("{}/update-dir", m_path);
        }
        auto GetDataBaseName() const -> const std::string
        {
            return "test-todo-database";
        }
        auto GetDataBaseDir() const -> const std::string
        {
            return fmt::format("{}/{}", m_path, GetDataBaseName());
        }

       protected:
        void InitJSONQueryWorkDir(const PreparedDir& dir)
        {
            //////////////////////////////////////////////////////////////////
            Utility::MakeDir(dir.GetEmptyDir());
            Utility::MakeDir(dir.GetInsertIntoDir());
            Utility::MakeDir(dir.GetUpdateDir());
            Utility::MakeDir(dir.GetSelectDir());
            Utility::MakeDir(dir.GetDeleteDir());
            Utility::MakeDir(dir.GetDataBaseDir());
            //////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////
            CreateDatabaseAt(Utility::GetBaseDir(dir.GetDataBaseDir()),
                             dir.GetDataBaseName());
            //////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////
            m_insertIntoPaths = CreateInsertIntoQueries(dir.GetInsertIntoDir());
            m_updatePaths     = CreateUpdateQueries(dir.GetUpdateDir());
            m_selectPaths     = CreateSelectQueries(dir.GetSelectDir());
            m_deletePaths     = CreateDeleteQueries(dir.GetDeleteDir());
            //////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////////////////////////
            SaveDeleteResultCategories(GetResultDir());
            SaveDeleteResultTaskcategories(GetResultDir());
            SaveDeleteResultTasks(GetResultDir());

            SaveInsertResultCategories(GetResultDir());
            SaveInsertResultTaskcategories(GetResultDir());
            SaveInsertResultTasks(GetResultDir());

            SaveSelectResultCategories(GetResultDir());
            SaveSelectResultTaskcategories(GetResultDir());
            SaveSelectResultTasks(GetResultDir());

            SaveUpdateResultCategories(GetResultDir());
            SaveUpdateResultTaskcategories(GetResultDir());
            SaveUpdateResultTasks(GetResultDir());
            //////////////////////////////////////////////////////////////////
        }

       protected:
        std::shared_ptr<std::vector<std::string>> m_insertIntoPaths;
        std::shared_ptr<std::vector<std::string>> m_updatePaths;
        std::shared_ptr<std::vector<std::string>> m_selectPaths;
        std::shared_ptr<std::vector<std::string>> m_deletePaths;
        std::string m_path;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreatePreparedDir(const std::string& path) -> UPreparedDir
    {
        return std::make_unique<PreparedDir>(path);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
