
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <boost/optional/optional.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "db-local-json-stream.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DataBaseWriter : public Interface::IDataBaseWriter
    {
       protected:
        DataBaseWriter(const std::string& path) : m_path{path}
        {
        }

       public:
        void Write(const Interface::IDataBase& database) const override
        {
            Interface::NotImplYet("DataBaseWriter::Read()");

            /*
            {
                "table-name" : "name"
                {
                    
                }
            }
            */
        }

       public:
        static auto Create(const std::string& path)
            -> Interface::UDataBaseWriter
        {
            Interface::UDataBaseWriter uwriter{new DataBaseWriter{path}};
            return (uwriter);
        }

       protected:
        std::string m_path;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateDBLocalJSONWriter(const std::string& path)
        -> Interface::UDataBaseWriter
    {
        return DataBaseWriter::Create(path);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
