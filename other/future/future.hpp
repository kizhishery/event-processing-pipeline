#pragma once

#include <string>
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

class Future {
public:
    static json processFutureNSE(const json& jsonData);
    static json processFutureBSE(const json& jsonData);
};
