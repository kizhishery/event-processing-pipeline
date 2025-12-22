#pragma once

#include <string>
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

class Equity {
public:
    static json processEquityExchangeOne(const json& jsonData);
    static json processEquityExchangeTwo(const json& jsonData);
};