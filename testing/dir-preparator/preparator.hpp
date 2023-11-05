
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>

#include "sharelib.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::Core
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IObject
    {
       public:
        virtual ~IObject() = default;

       public:
        virtual void Create()  = 0;
        virtual void Destroy() = 0;

       public:
        virtual void SetPath(const std::string &)   = 0;
        virtual auto GetPath() -> const std::string = 0;
        virtual void SetName(const std::string &)   = 0;
        virtual auto GetName() -> const std::string = 0;
    };

    using UObject = std::unique_ptr<IObject>;

    //////////////////////////////////////////////////////////////////

    class IFile;
    using UFile = std::unique_ptr<IFile>;

    class PROJECT_SHARED_EXPORT IFile : public IObject
    {
       public:
        virtual void AddLine(const std::string &text) = 0;
    };

    auto PROJECT_SHARED_EXPORT CreateFile(const std::string &name) -> UFile;

    //////////////////////////////////////////////////////////////////

    class IDirectory;
    using UDirectory = std::unique_ptr<IDirectory>;

    class PROJECT_SHARED_EXPORT IDirectory : public IObject
    {
       public:
        virtual void AddComponent(UObject object) = 0;
    };

    auto PROJECT_SHARED_EXPORT CreateDirectory(const std::string &name)
        -> UDirectory;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::Core

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////