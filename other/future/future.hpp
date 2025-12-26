#pragma once

#include <string>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class Future {
public:
    static json processFutureExchangeOne(const json& jsonData);
    static json processFutureExchangeTwo(const json& jsonData);
};
