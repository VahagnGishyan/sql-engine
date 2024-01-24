
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-column-element.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBaseNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT ColumnElement : public Interface::IColumnElement
    {
       protected:
        using DynamicValue   = Interface::DynamicValue;
        using IColumnElement = Interface::IColumnElement;
        using UColumnElement = Interface::UColumnElement;

       protected:
        ColumnElement(const DynamicValue& value);

       public:
        static auto Create(const DynamicValue& value = DynamicValue{})
            -> UColumnElement;
        static auto Create(const IColumnElement& element) -> UColumnElement;

       public:
        auto Copy() const -> UColumnElement override;

       public:
        void SetValue(const DynamicValue& value) override;
        void SetValue(const IColumnElement& element) override;
        auto GetValue() -> DynamicValue& override;
        auto GetValue() const -> const DynamicValue& override;

       public:
        bool Equal(const DynamicValue& value) const override;
        bool Equal(const IColumnElement& element) const override;

        bool NotEqual(const DynamicValue& value) const override;
        bool NotEqual(const IColumnElement& element) const override;

        bool GreaterThan(const DynamicValue& value) const override;
        bool GreaterThan(const IColumnElement& element) const override;

        bool LessThan(const DynamicValue& value) const override;
        bool LessThan(const IColumnElement& element) const override;

        bool GreaterThanOrEqualTo(const DynamicValue& value) const override;
        bool GreaterThanOrEqualTo(const IColumnElement& element) const override;

        bool LessThanOrEqualTo(const DynamicValue& value) const override;
        bool LessThanOrEqualTo(const IColumnElement& element) const override;

       protected:
        DynamicValue m_value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBaseNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
