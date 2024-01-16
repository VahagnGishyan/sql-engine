
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "dyn-object.hpp"
#include "interface/i-column-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::TableNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT ColumnElement : public Interface::IColumnElement
    {
       public:
        auto Copy() const -> Interface::UColumnElement override;
        auto CopyValue() const -> Interface::UDynamicValue override;
        auto IsNull() const -> bool override;

       public:
        void SetValue(const IDynamicValue& obj, const Interface::DynamicType& type) override;
        void SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value) override;
        void SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value) override;
        void SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value) override;

       public:
        auto GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type& override;
        auto GetValueAsDouble() const
            -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type& override;
        auto GetValueAsString() const
            -> const Interface::GetDynamicType<Interface::DynamicType::String>::type& override;

       public:
        bool Equal(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool NotEqual(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool GreaterThan(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool LessThan(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool GreaterThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type) override;
        bool LessThanOrEqualTo(const IDynamicValue& value, const Interface::DynamicType& type) override;

       protected:
        Interface::UDynamicValue m_pValue;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::TableNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
