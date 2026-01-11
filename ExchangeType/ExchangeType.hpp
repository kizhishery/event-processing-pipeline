#pragma once
#include <string>
#include <cstdlib>

#include "../Enums/Enums.hpp"
#include "../macro/logger.hpp"
#include "../namespace/data.hpp"

class ExchangeType {
public:
    static Type toType(const std::string& s);
    static Exchange toExchange(const std::string& s);
};
