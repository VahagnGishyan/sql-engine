
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include "interface/i-row.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::DataBaseNS
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class PROJECT_SHARED_EXPORT Row : public Interface::IRow
    {
       protected:
        using DynamicValue = Interface::DynamicValue;
        using IRowElement  = Interface::IRowElement;
        using URowElement  = Interface::URowElement;

       protected:
        Row(const unsigned int columnIndex);

       public:
        static auto Create(const unsigned int columnIndex) -> Interface::URow;

       public:
        auto Copy(const unsigned int rowindex) const -> URow override;

       public:
        auto GetSize() const -> unsigned int override;

       public:
        void AddElement(const Interface::IColumnElement& element,
                        const Interface::IColumn& column) override;
        auto GetElement(const int& index) -> Interface::IRowElement& override;
        auto GetElement(const int& index) const
            -> const Interface::IRowElement& override;

       protected:
        unsigned int m_rowIndex;
        Interface::RowElementList m_elements;
        std::vector<std::string> m_columnNames;  // used for indexing columns
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::DataBaseNS

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
