
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "application.hpp"
#include "info.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Application
{
    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //////////////////////////////////////////////////////////////////////////

    class EasyInfo : public Info
    {
    public:
        EasyInfo(const std::string &name, const std::string &version) : m_name{name}, m_version{version}
        {
        }

    public:
        virtual auto GetName() const -> const std::string & override
        {
            return m_name;
        }
        virtual auto GetVersion() const -> const std::string & override
        {
            return m_version;
        }

    protected:
        std::string m_name;
        std::string m_version;
    };

    //////////////////////////////////////////////////////////////////////////

    auto GetInfo() -> const Info &
    {
        static UInfo info = std::make_unique<EasyInfo>(APP_INFO_NAME, APP_INFO_VERSION);
        return *info;
    }

    //////////////////////////////////////////////////////////////////////////
    //                                                                      //
    //////////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
