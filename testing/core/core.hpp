
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "utility/defines.hpp"
#include <list>
#include <string>
#include <memory>

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Core
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT Object
    {
    public:
        virtual ~Object() = default;

    public:
        virtual void Create() = 0;
        virtual void Destroy() = 0;

    public:
        void SetPath(const std::string &);
        auto GetPath() -> const std::string;
        void SetName(const std::string &);
        auto GetName() -> const std::string;

    protected:
        std::string m_path;
        std::string m_name;
    };

    using UObject = std::unique_ptr<Object>;

    //////////////////////////////////////////////////////////////////

    class File;
    using UFile = std::unique_ptr<File>;

    class PROJECT_SHARED_EXPORT File : public Object
    {
    public:
        File(const std::string &name);
        ~File();

    public:
        void Create() override;
        void Destroy() override;

    public:
        void AddLine(const std::string &text);

    public:
        static auto CreateInstance(const std::string &name) -> UFile;

    protected:
        std::list<std::string> m_content;
    };

    //////////////////////////////////////////////////////////////////

    class Directory;
    using UDirectory = std::unique_ptr<Directory>;

    class PROJECT_SHARED_EXPORT Directory : public Object
    {
    public:
        Directory(const std::string &name);
        ~Directory();

    public:
        void Create() override;
        void Destroy() override;

    public:
        static auto CreateInstance(const std::string &name) -> UDirectory;

    public:
        void AddComponent(UObject object);

    protected:
        std::list<UObject> m_content;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
