
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column-constraint.hpp"

#include <fmt/format.h>

#include <stdexcept>

#include "interface/i-column.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Table
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintNotNull::Copy() const -> Interface::UColumnConstraint
    {
        return std::make_unique<ConstraintNotNull>();
    }

    void ConstraintNotNull::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        if (element.IsNull() == true)
        {
            throw std::logic_error("ConstraintNotNull, element is null");
        }
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintUnique::Copy() const -> Interface::UColumnConstraint
    {
        return std::make_unique<ConstraintUnique>();
    }

    void ConstraintUnique::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        column.ForEach(
            [&column, &element](const Interface::IColumnElement& item)
            {
                if (element.Equal(item, column.GetType()) == true)
                {
                    throw std::logic_error("ConstraintUnique, element is not unique");
                }
            });
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintPrimaryKey::Copy() const -> Interface::UColumnConstraint
    {
        return std::make_unique<ConstraintPrimaryKey>();
    }

    void ConstraintPrimaryKey::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        Utility::Assert(column.GetType() == Interface::DynamicType::Int,
                        fmt::format("ConstraintPrimaryKey, column type must be Int, but it is: {}",
                                    Interface::GetDynamicTypeNameAsString(column.GetType())));
        column.ForEach(
            [&column, &element](const Interface::IColumnElement& item)
            {
                if ((element.IsNull() == true) && (element.Equal(item, column.GetType()) == true))
                {
                    throw std::logic_error("ConstraintPrimaryKey, element is null or not unique");
                }
            });
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintForeignKey::Copy() const -> Interface::UColumnConstraint
    {
        return std::make_unique<ConstraintForeignKey>();
    }

    void ConstraintForeignKey::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        Utility::Assert(column.GetType() == Interface::DynamicType::Int,
                        fmt::format("ConstraintForeignKey, column type must be Int, but it is: {}",
                                    Interface::GetDynamicTypeNameAsString(column.GetType())));
        column.ForEach(
            [&column, &element](const Interface::IColumnElement& item)
            {
                if ((element.IsNull() == true))
                {
                    throw std::logic_error("ConstraintForeignKey, element is null");
                }
            });
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintCheck::Copy() const -> Interface::UColumnConstraint
    {
        throw std::logic_error{"ConstraintCheck is not impl yet."};
        // return std::make_unique<ConstraintCheck>();
    }

    void ConstraintCheck::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        throw std::logic_error{"ConstraintCheck is not impl yet."};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintDefault::Copy() const -> Interface::UColumnConstraint
    {
        auto&& copy = std::make_unique<ConstraintDefault>();
        copy->SetDefaultValue(m_value->CopyValue());
        return std::move(copy);
    }

    void ConstraintDefault::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        throw std::logic_error{"ConstraintDefault is not impl yet."};
    }

    //////////////////////////////////////////////////////////////////////

    auto ConstraintDefault::GetValue() const -> const Interface::IDynamicValue&
    {
        return *m_value;
    }

    void ConstraintDefault::SetDefaultValue(Interface::UDynamicValue value)
    {
        m_value = std::move(value);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ConstraintCreateIndex::Copy() const -> Interface::UColumnConstraint
    {
        throw std::logic_error{"ConstraintCreateIndex is not impl yet."};
        // return std::make_unique<ConstraintCheck>();
    }

    void ConstraintCreateIndex::Perform(const Interface::IColumn& column, Interface::IColumnElement& element) const
    {
        throw std::logic_error{"ConstraintCreateIndex is not impl yet."};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Table

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
