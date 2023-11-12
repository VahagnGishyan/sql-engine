
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "app-info/application.hpp"
#include "db-filestream.hpp"
#include "db-manager.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto DBManagerInit::GetWorkDir() const -> const std::string
    {
        return (m_workdir);
    }

    auto DBManagerInit::GetName() const -> const std::string
    {
        return (m_name);
    }

    auto DBManagerInit::GetFileStream() const -> ShFileStream
    {
        return (m_filestream);
    }

    //////////////////////////////////////////////////////////////////////

    void DBManagerInit::SetWorkDir(const std::string& workdir)
    {
        m_workdir = workdir;
    }
    void DBManagerInit::SetName(const std::string& name)
    {
        m_name = name;
    }
    void DBManagerInit::SetFileStream(ShFileStream filestream)
    {
        m_filestream = filestream;
    }

    //////////////////////////////////////////////////////////////////////

    static auto GetDBManagerWorkDir() -> const std::string
    {
        auto&& info       = Application::GetInfo();
        auto&& prjAppData = info.GetDefaultAppData();
        auto&& workdir    = prjAppData + "/main";
        return (workdir);
    }

    auto DBManagerInit::Create(const std::string& name, ShFileStream filestream)
        -> UDBManagerInit
    {
        auto init = std::make_unique<DBManagerInit>();
        if (filestream == nullptr)
        {
            filestream = std::move(FileStream::Create());
        }
        init->SetWorkDir(GetDBManagerWorkDir());
        init->SetName(name);
        init->SetFileStream(filestream);
        return std::move(init);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
