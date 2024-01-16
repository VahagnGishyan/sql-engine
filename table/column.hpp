
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <string>

#include "interface/i-column.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::TableNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class Column : public Interface::IColumn
    {
       protected:
        Column(const std::string& name, const Interface::DynamicType& type);

       public:
        static auto Create(const std::string& name,
                           const Interface::DynamicType& type)
            -> Interface::UColumn;

       public:
        auto Copy(const std::string& newname) const
            -> Interface::UColumn override;

       public:
        auto GetName() const -> const std::string& override;
        auto GetSize() const -> unsigned int override;

       public:
        auto GetType() const -> const Interface::DynamicType override;
        void SetType(const Interface::DynamicType& type) override;

       public:
        auto At(const int index) -> Interface::IColumnElement& override;
        void AddElement(Interface::UColumnElement element) override;
        auto GetElement(const int& index)
            -> Interface::IColumnElement& override;

       protected:
        std::string m_name;
        Interface::DynamicType m_type;
        Interface::ColumnElementList m_elements;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::TableNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
