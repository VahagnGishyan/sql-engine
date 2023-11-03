
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

    class PROJECT_SHARED_EXPORT File : Object
    {
    public:
        void Create() override;
        void Destroy() override;

    public:
        void AddLine(const std::string &text);

    public:
        static auto CreateInstance() -> UObject;

    protected:
        std::list<std::string> m_content;
    };

    //////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT Directory : Object
    {
    public:
        void Create() override;
        void Destroy() override;

    public:
        static auto CreateInstance() -> UObject;

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
