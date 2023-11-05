
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "impl.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
// #include "utility/filesystem.hpp"

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

    File::File(const std::string &name)
    {
        SetName(name);
    }

    File::~File()
    {
        Destroy();
    }

    void File::Create()
    {
        std::string basedir = GetPath();
        std::string filename = GetName();
        std::string filepath = basedir + "/" + filename;

        // Open the file in output mode, which creates the file if it doesn't exist
        // std::cout << "File::Create(), path: " << filepath << std::endl;
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

    void File::SetPath(const std::string &path)
    {
        m_filepath = path;
    }
    auto File::GetPath() -> const std::string
    {
        return (m_filepath);
    }
    void File::SetName(const std::string &name)
    {
        m_filename = name;
    }
    auto File::GetName() -> const std::string
    {
        return (m_filename);
    }

    void File::AddLine(const std::string &text)
    {
        m_content.push_back(text);
    }

    auto File::CreateInstance(const std::string &name) -> UFile
    {
        return std::make_unique<File>(name);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
