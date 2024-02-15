
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include <fmt/core.h>

#include <stdexcept>

#include "database.hpp"
#include "utility/core.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBase
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    using DynamicType       = Interface::DynamicType;
    using DynamicValue      = Interface::DynamicValue;
    using UDynamicValue     = Interface::UDynamicValue;
    using ColumnElementList = Interface::ColumnElementList;

    class Column : public Interface::IColumn
    {
       protected:
        Column(const std::string& name, const Interface::DynamicType& type) :
            m_name{name}, m_type{type}, m_elements{}
        // , m_constraintList{nullptr}
        {
        }

       public:
        static auto Create(const std::string& name,
                           const Interface::DynamicType& type)
            -> Interface::UColumn
        {
            Interface::UColumn ucolumn{
                new Column{name, type}
            };
            return (ucolumn);
        }

       public:
        auto Copy() const -> Interface::UColumn override
        {
            return Copy(m_name);
        }

        auto Copy(const std::string& newname) const
            -> Interface::UColumn override
        {
            auto&& newcolumn = Create(newname, m_type);
            for (auto&& item : m_elements)
            {
                newcolumn->AddElement(Interface::CopyUDynValue(item));
            }
            return std::move(newcolumn);
        }

       public:
        auto GetName() const -> const std::string& override
        {
            return m_name;
        }
        void SetName(const std::string& name) override
        {
            m_name = name;
        }

        auto GetSize() const -> int override
        {
            return static_cast<int>(m_elements.size());
        }

       public:
        auto GetType() const -> const Interface::DynamicType override
        {
            return m_type;
        }
        void SetType(const Interface::DynamicType& type) override
        {
            m_type = type;
        }

       public:
        void AddElement(const DynamicValue& element) override
        {
            AddElement(Interface::CreateUDynValue(element));
        }
        void AddElement(UDynamicValue element) override
        {
            if (element != nullptr)
            {
                Utility::Assert(Interface::IsDynamicValueType(*element, m_type),
                                "AddElement(UDynamicValue element)");
            }
            m_elements.push_back(std::move(element));
        }

        // temp, untestes
        void SetElement(const int& index, const DynamicValue& element) override
        {
            SetElement(index, Interface::CreateUDynValue(element));
        }
        void SetElement(const int& index, UDynamicValue element) override
        {
            if (element != nullptr)
            {
                if (Interface::IsDynamicValueType(*element, m_type) == false)
                {
                    auto&& strElement =
                        Interface::ConvertUDynValueToString(element);
                    auto&& strExpectedType =
                        Interface::GetDynamicTypeNameAsString(m_type);
                    auto&& strActualType =
                        Interface::GetDynamicTypeNameAsString(
                            Interface::GetRealType(element));
                    throw std::logic_error{fmt::format(
                        "SetElement(UDynamicValue element = {}), "
                        "expected-type = {}, actual-type = {}",
                        strElement, strExpectedType, strActualType)};
                }
            }
            m_elements.at(index) = std::move(element);
        }

        auto GetElement(const int& index) const -> const UDynamicValue& override
        {
            return m_elements.at(index);
        }

        void RemoveElement(const int index) override
        {
            Utility::Assert(m_elements.size() > index,
                            "Column::RemoveElement(index), index out of range");
            m_elements.erase(m_elements.begin() + index);
        }

       protected:
        std::string m_name;
        DynamicType m_type;
        ColumnElementList m_elements;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto CreateColumn(const std::string& name,
                      const Interface::DynamicType& type) -> Interface::UColumn
    {
        return Column::Create(name, type);
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBase

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
