
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

namespace SQLEngine::DataBaseNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT Column : public Interface::IColumn
    {
       protected:
        Column(const std::string& name, const Interface::DynamicType& type);

       public:
        static auto Create(const std::string& name,
                           const Interface::DynamicType& type)
            -> Interface::UColumn;

       public:
        auto Copy() const -> Interface::UColumn override;
        auto Copy(const std::string& newname) const
            -> Interface::UColumn override;

       public:
        auto GetName() const -> const std::string& override;
        void SetName(const std::string& name) override;
        auto GetSize() const -> unsigned int override;

       public:
        auto GetType() const -> const Interface::DynamicType override;
        void SetType(const Interface::DynamicType& type) override;

       public:
        void AddElement(Interface::UColumnElement element) override;
        auto GetElement(const int& index)
            -> Interface::IColumnElement& override;
        auto GetElement(const int& index) const
            -> const Interface::IColumnElement& override;

       protected:
        std::string m_name;
        Interface::DynamicType m_type;
        Interface::ColumnElementList m_elements;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBaseNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
