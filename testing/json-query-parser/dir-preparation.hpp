
//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>

#include "interface/i-database.hpp"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

namespace SQLEngine::Testing::JSONQueryParser::Preparation
{
    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////

    void InitAt(const std::string &);

    auto GetDatabase() -> Interface::UDataBase;

    auto GetEmptyDir() -> const std::string;
    auto GetResultDir() -> const std::string;

    auto GetInsertJSONFileExample() -> const std::string;
    auto GetUpdateJSONFileExample() -> const std::string;
    auto GetSelectJSONFileExample() -> const std::string;
    auto GetDeleteJSONFileExample() -> const std::string;

    auto GetInsertJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;
    auto GetUpdateJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;
    auto GetSelectJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;
    auto GetDeleteJSONExamples()
        -> const std::shared_ptr<std::vector<std::string>>;

    //////////////////////////////////////////////////////////////////////
    //                                                                  //
    //////////////////////////////////////////////////////////////////////
}  // namespace SQLEngine::Testing::JSONQueryParser::Preparation

//////////////////////////////////////////////////////////////////////////
//                                                                      //
//////////////////////////////////////////////////////////////////////////
