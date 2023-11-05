
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <filesystem>
#include <fstream>
#include <iostream>

#include "impl.hpp"
#include "utility/filesystem.hpp"

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Core
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    namespace fs = std::filesystem;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    Directory::Directory(const std::string &name)
    {
        SetName(name);
    }

    void Directory::Create()
    {
        std::string basedir  = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

        // std::cout << "Directory::Create(), path: " << filepath << std::endl;
        if (!fs::create_directory(filepath))
        {
            throw std::runtime_error("Failed to create directory: " + filepath);
        }

        std::for_each(m_content.begin(), m_content.end(),
                      [filepath](const UObject &element)
                      {
                          element->SetPath(filepath);
                          element->Create();
                      });
    }
    void Directory::Destroy()
    {
        std::string basedir  = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

        if (Utility::IsPathExists(filepath) == false)
        {
            return;
        }

        std::for_each(m_content.rbegin(), m_content.rend(),
                      [](const UObject &element)
                      {
                          element->Destroy();
                      });

        try
        {
            fs::remove_all(filepath);
        }
        catch (const fs::filesystem_error &exception)
        {
            throw std::runtime_error("Failed to remove directory: " + filepath +
                                     "what: " + exception.what());
        }
    }

    void Directory::SetPath(const std::string &path)
    {
        m_basedirpath = path;
    }
    auto Directory::GetPath() -> const std::string
    {
        return (m_basedirpath);
    }
    void Directory::SetName(const std::string &name)
    {
        m_dirname = name;
    }
    auto Directory::GetName() -> const std::string
    {
        return (m_dirname);
    }

    void Directory::AddComponent(UObject object)
    {
        m_content.push_back(std::move(object));
    }

    auto Directory::CreateInstance(const std::string &name) -> UDirectory
    {
        return std::make_unique<Directory>(name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::Core

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
