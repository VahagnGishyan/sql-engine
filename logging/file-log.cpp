
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "file-log.hpp"
#include "application.hpp"
#include "utility/filesystem.hpp"
#include "utility/core.hpp"
#include <fstream>
#include <fmt/core.h>

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Logging
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    auto FileLog::GetDefaultLogPath() -> const std::string
    {
        std::string path = Utility::GetDefaultDataPath();
        auto &&info = Application::GetInfo();
        path = fmt::format("{}/easy-log/{}.txt", path, info.GetName());
        return path;
    }

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    class EasyFileLog : public FileLog
    {
    public:
        EasyFileLog()
        {
            std::string path = FileLog::GetDefaultLogPath();
            m_ofile.open(path);
            if (!m_ofile)
            {
                throw std::invalid_argument(fmt::format("Can not open file, path: {}", path));
            }
        }

    public:
        void Write(const std::string &message) override
        {
            m_ofile << message;
        }

        void WriteLine(const std::string &message) override
        {
            m_ofile << message << std::endl;
        }

    protected:
        std::ofstream m_ofile;
    };

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
