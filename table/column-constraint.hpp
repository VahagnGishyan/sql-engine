
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-column-constraint.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class ConstraintNotNull : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;
    };

    //////////////////////////////////////////////////////////////////////

    class ConstraintUnique : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;
    };

    //////////////////////////////////////////////////////////////////////

    class ConstraintPrimaryKey : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;
    };

    //////////////////////////////////////////////////////////////////////

    class ConstraintForeignKey : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;
    };

    //////////////////////////////////////////////////////////////////////

    class ConstraintCheck : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;
    };

    //////////////////////////////////////////////////////////////////////

    class ConstraintDefault : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;

       public:
        virtual void SetDefaultValue(Interface::UDynamicValue value);
        virtual auto GetValue() const -> const Interface::IDynamicValue&;

       protected:
        Interface::UDynamicValue m_value;
    };

    //////////////////////////////////////////////////////////////////////

    class ConstraintCreateIndex : public Interface::IColumnConstraint
    {
       public:
        auto Copy() const -> Interface::UColumnConstraint override;
        void Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const override;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
