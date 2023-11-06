
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <list>

#include "preparator.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Core
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    // class Object : IObject
    // {
    // public:
    //     void SetPath(const std::string &) override;
    //     auto GetPath() -> const std::string override;
    //     void SetName(const std::string &) override;
    //     auto GetName() -> const std::string override;

    // protected:
    //     std::string m_path;
    //     std::string m_name;
    // };

    //////////////////////////////////////////////////////////////////

    class File final : public IFile
    {
       public:
        File(const std::string &name);

       public:
        void Create() override;
        void Destroy() override;

       public:
        void SetPath(const std::string &) override;
        auto GetPath() -> const std::string override;
        void SetName(const std::string &) override;
        auto GetName() -> const std::string override;

       public:
        void AddLine(const std::string &text) override;

       public:
        static auto CreateInstance(const std::string &name) -> UFile;

       protected:
        std::string m_filepath;
        std::string m_filename;
        std::list<std::string> m_content;
    };

    //////////////////////////////////////////////////////////////////

    class Directory final : public IDirectory
    {
       public:
        Directory(const std::string &name);

       public:
        void Create() override;
        void Destroy() override;

       public:
        void SetPath(const std::string &) override;
        auto GetPath() -> const std::string override;
        void SetName(const std::string &) override;
        auto GetName() -> const std::string override;

       public:
        void AddComponent(UObject object) override;

       public:
        static auto CreateInstance(const std::string &name) -> UDirectory;

       protected:
        std::string m_basedirpath;
        std::string m_dirname;
        std::list<UObject> m_content;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::Core

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
