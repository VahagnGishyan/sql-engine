
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "dyn-object.hpp"
#include "interface/i-row-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT RowElement : public Interface::IRowElement
    {
       public:
        auto Copy() const -> Interface::URowElement override;
        auto CopyObject() const -> Interface::UDynamicObject override;
        auto CopyValue() const -> Interface::UDynamicValue override;
        auto IsNull() const -> bool override;

       public:
        auto GetType() const -> const Interface::DynamicType& override;

       public:
        void SetValue(const IDynamicObject& obj) override;
        void SetValueAsInt(const Interface::GetDynamicType<Interface::DynamicType::Int>::type& value) override;
        void SetValueAsDouble(const Interface::GetDynamicType<Interface::DynamicType::Double>::type& value) override;
        void SetValueAsString(const Interface::GetDynamicType<Interface::DynamicType::String>::type& value) override;

       public:
        auto GetValue() const -> const Interface::IDynamicValue& override;
        auto GetValueAsInt() const -> const Interface::GetDynamicType<Interface::DynamicType::Int>::type& override;
        auto GetValueAsDouble() const
            -> const Interface::GetDynamicType<Interface::DynamicType::Double>::type& override;
        auto GetValueAsString() const
            -> const Interface::GetDynamicType<Interface::DynamicType::String>::type& override;

       public:
        void AssertTypeIs(const Interface::DynamicType& type) const override;
        void AssertTypeIsNot(const Interface::DynamicType& type) const override;

       public:
        bool Equal(const IDynamicObject& element) override;
        bool NotEqual(const IDynamicObject& element) override;
        bool GreaterThan(const IDynamicObject& element) override;
        bool LessThan(const IDynamicObject& element) override;
        bool GreaterThanOrEqualTo(const IDynamicObject& element) override;
        bool LessThanOrEqualTo(const IDynamicObject& element) override;

       protected:
        Interface::UDynamicObject m_pobject;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
