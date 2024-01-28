
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "db-local-json-stream.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class DataBaseReader : public Interface::IDataBaseReader
    {
       protected:
        DataBaseReader(const std::string& path, const std::string& name) :
            m_path{path}, m_name{name}
        {
        }

       public:
        auto Read() const -> Interface::UDataBase override
        {
            Interface::NotImplYet("DataBaseReader::Read()");
            return nullptr;
        }

       public:
        static auto Create(const std::string& path, const std::string& name)
            -> Interface::UDataBaseReader
        {
            Interface::UDataBaseReader ureader{
                new DataBaseReader{path, name}
            };
            return (ureader);
        }

       protected:
        std::string m_path;
        std::string m_name;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateDBLocalJSONReader(const std::string& path,
                                 const std::string& name)
        -> Interface::UDataBaseReader
    {
        return DataBaseReader::Create(path, name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
