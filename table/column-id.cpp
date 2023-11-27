
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "column-id.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Interface
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto ColumnID::GetName() const -> const std::string
    {
        return m_name;
    }

    void ColumnID::SetName(const std::string& name)
    {
        m_name = name;
    }

    //////////////////////////////////////////////////////////////////////

    auto ColumnID::Copy() const -> UColumnID
    {
        auto id    = std::make_unique<ColumnID>();
        id->m_name = m_name;
        return id;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Interface

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
