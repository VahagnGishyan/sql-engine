
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

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    enum class DynamicObjectType
    {
        Unset,
        Int,
        Double,
        String
    };

    auto GetDynamicObjectTypeNameAsString(const DynamicObjectType& type) -> const std::string&;

    //////////////////////////////////////////////////////////////////////

    template <DynamicObjectType DynType>
    class GetDynamicObjectType;

    template <>
    class GetDynamicObjectType<DynamicObjectType::Int>
    {
       public:
        using type = int;
    };

    template <>
    class GetDynamicObjectType<DynamicObjectType::Double>
    {
       public:
        using type = double;
    };

    template <>
    class GetDynamicObjectType<DynamicObjectType::String>
    {
       public:
        using type = std::string;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDynamicObject
    {
       public:
        virtual ~IDynamicObject() = default;

       public:
        virtual auto GetType() const -> const DynamicObjectType& = 0;
        virtual void SetType(const DynamicObjectType& type)      = 0;

       public:
        virtual void SetValueAsInt(const GetDynamicObjectType<DynamicObjectType::Int>::type& value)       = 0;
        virtual void SetValueAsDouble(const GetDynamicObjectType<DynamicObjectType::Double>::type& value) = 0;
        virtual void SetValueAsString(const GetDynamicObjectType<DynamicObjectType::String>::type& value) = 0;

       public:
        virtual auto GetValueAsInt() const -> const GetDynamicObjectType<DynamicObjectType::Int>::type&       = 0;
        virtual auto GetValueAsDouble() const -> const GetDynamicObjectType<DynamicObjectType::Double>::type& = 0;
        virtual auto GetValueAsString() const -> const GetDynamicObjectType<DynamicObjectType::String>::type& = 0;

       public:
        virtual bool Equal(const IDynamicObject& element)                = 0;
        virtual bool NotEqual(const IDynamicObject& element)             = 0;
        virtual bool GreaterThan(const IDynamicObject& element)          = 0;
        virtual bool LessThan(const IDynamicObject& element)             = 0;
        virtual bool GreaterThanOrEqualTo(const IDynamicObject& element) = 0;
        virtual bool LessThanOrEqualTo(const IDynamicObject& element)    = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using UDynamicObject  = std::unique_ptr<IDynamicObject>;
    using ShDynamicObject = std::shared_ptr<IDynamicObject>;
    using WDynamicObject  = std::weak_ptr<IDynamicObject>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
