#pragma once
#include <string>
#include "../Enums/Enums.hpp"

class ExchangeType {
public:
    static Exchange toExchange(const std::string& s);
    static Type     toType(const std::string& s);
};
