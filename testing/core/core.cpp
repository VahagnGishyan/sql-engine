
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "core.hpp"
#include <filesystem>
#include <fstream>

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

    void Object::SetPath(const std::string &path)
    {
        m_path = path;
    }
    auto Object::GetPath() -> const std::string
    {
        return (m_path);
    }
    void Object::SetName(const std::string &name)
    {
        m_name = name;
    }
    auto Object::GetName() -> const std::string
    {
        return (m_name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void File::Create()
    {
        std::string basedir = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

        // Open the file in output mode, which creates the file if it doesn't exist
        std::ofstream outputFile(filepath);

        // Check if the file is successfully opened
        if (!outputFile)
        {
            // Handle error, for example, throw an exception
            throw std::runtime_error("Failed to open the file for writing.");
        }

        // Write the content to the file
        for (const std::string &line : m_content)
        {
            outputFile << line << std::endl;
        }
    }

    void File::Destroy()
    {
        std::string basedir = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

        // Use std::remove to delete the file
        if (std::remove(filepath.c_str()) != 0)
        {
            // Handle error, for example, throw an exception
            throw std::runtime_error("Failed to delete the file.");
        }
    }

    void File::AddLine(const std::string &text)
    {
        m_content.push_back(text);
    }

    auto File::CreateInstance() -> UObject
    {
        return UObject{new File{}};
    }

    //////////////////////////////////////////////////////////////////

    void Directory::Create()
    {
        std::string basedir = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

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
        std::string basedir = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

        std::for_each(m_content.rbegin(), m_content.rend(),
                      [](const UObject &element)
                      {
                          element->Destroy();
                      });

        try
        {
            fs::remove_all(filepath);
        }
        catch (const fs::filesystem_error &e)
        {
            throw std::runtime_error("Failed to remove directory: " + filepath);
        }
    }

    auto Directory::CreateInstance() -> UObject
    {
        return UObject{new Directory{}};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
