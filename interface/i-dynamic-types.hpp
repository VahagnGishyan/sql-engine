
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <variant>

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
        Int,
        Double,
        String
    };

    auto GetDynamicTypeNameAsString(const DynamicType& type)
        -> const std::string&;

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

    /*
     * For a column element, we require a dynamic element capable of changing
     * its value type, transitioning, for instance, from int to double. However,
     * this element should not be aware of its type, and the type information
     * will be stored in the column.
     * Additionally, a row element, similar to a column element, it should be
     * able to change its value type, but the row element should be aware of its
     * own type.
     *
     * A dynamic type without type information has been named DynamicValue,
     * while a dynamic type with type information has been named DynamicObject.
     */

    //////////////////////////////////////////////////////////////////////

    using DynamicValue = std::variant<
        Interface::GetDynamicType<Interface::DynamicType::Int>::type,
        Interface::GetDynamicType<Interface::DynamicType::Double>::type,
        Interface::GetDynamicType<Interface::DynamicType::String>::type>;

    // using UDynamicValueType = std::unique_ptr<DynamicValue>;

    //////////////////////////////////////////////////////////////////////

    struct PROJECT_SHARED_EXPORT DynamicObject final
    {
        DynamicType type;
        DynamicValue value;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
