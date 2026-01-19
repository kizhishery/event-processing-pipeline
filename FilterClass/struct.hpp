#pragma once

#include <string>

#include "../ExchangeType/ExchangeType.hpp"

struct Pair {
    Exchange exchange;
    Type type;

    Pair() : exchange(Exchange::UNKNOWN), type(Type::UNKNOWN) {}
    // Parameterized constructor
    Pair(std::string _exchange, std::string  _type) {
        type = ExchangeType::toType(_type);
        exchange = ExchangeType::toExchange(_exchange);
    }
};