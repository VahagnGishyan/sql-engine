
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "db-manager-init.hpp"

#include "app-info/application.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DBLib::DBManager
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Init::GetWorkDir() const -> const std::string
    {
        return (m_workdir);
    }

    auto Init::GetName() const -> const std::string
    {
        return (m_name);
    }

    // auto Init::GetFileStream() const -> ShFileStream
    // {
    //     return (m_filestream);
    // }

    //////////////////////////////////////////////////////////////////////

    void Init::SetWorkDir(const std::string& workdir)
    {
        m_workdir = workdir;
    }
    void Init::SetName(const std::string& name)
    {
        m_name = name;
    }
    // void Init::SetFileStream(ShFileStream filestream)
    // {
    //     m_filestream = filestream;
    // }

    //////////////////////////////////////////////////////////////////////

    static auto GetDBManagerWorkDir() -> const std::string
    {
        auto&& info       = Application::GetInfo();
        auto&& prjAppData = info.GetDefaultAppData();
        auto&& workdir    = prjAppData + "/main";
        return (workdir);
    }

    auto Init::Create(const std::string& name) -> Interface::UDBManagerInit
    {
        Init obj;
        auto init = std::make_unique<Init>();
        // if (filestream == nullptr)
        // {
        //     filestream = std::move(FileStream::Create());
        // }
        init->SetWorkDir(GetDBManagerWorkDir());
        init->SetName(name);
        // init->SetFileStream(filestream);
        return std::move(init);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DBLib::DBManager

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
