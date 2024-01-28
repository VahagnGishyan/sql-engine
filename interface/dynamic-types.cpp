
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <map>
#include <stdexcept>
#include <variant>

#include "i-dynamic-types.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Interface::GetDynamicTypeNameAsString(const DynamicType& type)
        -> const std::string
    {
        static std::map<DynamicType, std::string> elements = {
            {DynamicType::Int,    "Unset" },
            {DynamicType::Int,    "Int"   },
            {DynamicType::Double, "Double"},
            {DynamicType::String, "String"},
        };
        static auto end = elements.end();

        auto pos = elements.find(type);
        Utility::Assert(
            pos != end,
            fmt::format(
                "GetDynamicTypeNameAsString, unknown DynamicType, id is [{}]",
                (int)type));
        return pos->second;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    bool Interface::IsDynamicValueType(const DynamicValue& value,
                                       const DynamicType& type)
    {
        switch (type)
        {
            case DynamicType::Int:
                return std::holds_alternative<
                    GetDynamicType<DynamicType::Int>::type>(value);
                break;
            case DynamicType::Double:
                return std::holds_alternative<
                    GetDynamicType<DynamicType::Double>::type>(value);
                break;
            case DynamicType::String:
                return std::holds_alternative<
                    GetDynamicType<DynamicType::String>::type>(value);
                break;
            default:
                throw std::logic_error{"Unknown DynamicValue type"};
        }
    }

    void Interface::AssertDynamicValueTypeIs(const DynamicValue& value,
                                             const DynamicType& type)
    {
        Utility::Assert(IsDynamicValueType(value, type),
                        "Interface::AssertDynamicValueTypeIs()");
    }

    auto Interface::CreateUDynValue(const DynamicValue& value) -> UDynamicValue
    {
        return std::make_unique<DynamicValue>(value);
    }

    auto Interface::CopyUDynValue(const UDynamicValue& value) -> UDynamicValue
    {
        if (value == nullptr)
        {
            return nullptr;
        }
        return std::make_unique<DynamicValue>(*value);
    }

    auto Interface::ConvertUDynValueToString(const UDynamicValue& value,
                                             const DynamicType& type)
        -> std::string
    {
        if (value == nullptr)
        {
            return "nullptr";
        }

        AssertDynamicValueTypeIs(*value, type);
        if (type == Interface::DynamicType::String)
        {
            return std::get<std::string>(*value);
        }

        if (type == Interface::DynamicType::Int)
        {
            auto result = std::get<int>(*value);
            return std::to_string(result);
        }

        if (type == Interface::DynamicType::Double)
        {
            auto result = std::get<double>(*value);
            return std::to_string(result);
        }

        throw std::logic_error{"Unknown DynamicValue type"};
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto Interface::AreValuesEqual(const UDynamicValue& lhs,
                                   const UDynamicValue& rhs) -> bool
    {
        if (lhs == nullptr)
        {
            return rhs == nullptr;
        }

        if (rhs == nullptr)
        {
            return false;
        }

        return (*lhs == *rhs);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
