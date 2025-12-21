#pragma once

#include <string>
#include <utility>
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

class Option {
public:
    static json processNSE(const json& side);
    static std::pair<int, int> calculateBound(double underlyingValue, int multiplier, int count);

    static json processOptionNSE(const json& jsonData);
    static json processOptionBSE(const json& jsonData);
};
