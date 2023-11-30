
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

    enum class DynamicType
    {
        Unset,
        Int,
        Double,
        String
    };

    auto GetDynamicTypeNameAsString(const DynamicType& type) -> const std::string&;

    //////////////////////////////////////////////////////////////////////

    template <DynamicType DynType>
    class GetDynamicType;

    template <>
    class GetDynamicType<DynamicType::Int>
    {
       public:
        using type = int;
    };

    template <>
    class GetDynamicType<DynamicType::Double>
    {
       public:
        using type = double;
    };

    template <>
    class GetDynamicType<DynamicType::String>
    {
       public:
        using type = std::string;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDynamicValue;

    using UDynamicValue  = std::unique_ptr<IDynamicValue>;
    using ShDynamicValue = std::shared_ptr<IDynamicValue>;
    using WDynamicValue  = std::weak_ptr<IDynamicValue>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDynamicValue
    {
       public:
        virtual ~IDynamicValue() = default;

       public:
        virtual auto CopyValue() const -> UDynamicValue = 0;
        virtual auto IsNull() const -> bool             = 0;

       public:
        virtual void SetValue(const IDynamicValue& obj, const DynamicType& type)              = 0;
        virtual void SetValueAsInt(const GetDynamicType<DynamicType::Int>::type& value)       = 0;
        virtual void SetValueAsDouble(const GetDynamicType<DynamicType::Double>::type& value) = 0;
        virtual void SetValueAsString(const GetDynamicType<DynamicType::String>::type& value) = 0;

       public:
        virtual auto GetValueAsInt() const -> const GetDynamicType<DynamicType::Int>::type&       = 0;
        virtual auto GetValueAsDouble() const -> const GetDynamicType<DynamicType::Double>::type& = 0;
        virtual auto GetValueAsString() const -> const GetDynamicType<DynamicType::String>::type& = 0;

       public:
        virtual bool Equal(const IDynamicValue& value, const DynamicType& type)                = 0;
        virtual bool NotEqual(const IDynamicValue& value, const DynamicType& type)             = 0;
        virtual bool GreaterThan(const IDynamicValue& value, const DynamicType& type)          = 0;
        virtual bool LessThan(const IDynamicValue& value, const DynamicType& type)             = 0;
        virtual bool GreaterThanOrEqualTo(const IDynamicValue& value, const DynamicType& type) = 0;
        virtual bool LessThanOrEqualTo(const IDynamicValue& value, const DynamicType& type)    = 0;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class IDynamicObject;

    using UDynamicObject  = std::unique_ptr<IDynamicObject>;
    using ShDynamicObject = std::shared_ptr<IDynamicObject>;
    using WDynamicObject  = std::weak_ptr<IDynamicObject>;

    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT IDynamicObject
    {
       public:
        virtual ~IDynamicObject() = default;

       public:
        virtual auto CopyObject() const -> UDynamicObject = 0;
        virtual auto CopyValue() const -> UDynamicValue   = 0;
        virtual auto IsNull() const -> bool               = 0;

       public:
        virtual auto GetType() const -> const DynamicType& = 0;

       public:
        virtual void SetValue(const IDynamicObject& obj)                                      = 0;
        virtual void SetValueAsInt(const GetDynamicType<DynamicType::Int>::type& value)       = 0;
        virtual void SetValueAsDouble(const GetDynamicType<DynamicType::Double>::type& value) = 0;
        virtual void SetValueAsString(const GetDynamicType<DynamicType::String>::type& value) = 0;

       public:
        virtual auto GetValue() const -> const IDynamicValue&                                     = 0;
        virtual auto GetValueAsInt() const -> const GetDynamicType<DynamicType::Int>::type&       = 0;
        virtual auto GetValueAsDouble() const -> const GetDynamicType<DynamicType::Double>::type& = 0;
        virtual auto GetValueAsString() const -> const GetDynamicType<DynamicType::String>::type& = 0;

       public:
        virtual void AssertTypeIs(const Interface::DynamicType& type) const    = 0;
        virtual void AssertTypeIsNot(const Interface::DynamicType& type) const = 0;

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
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
