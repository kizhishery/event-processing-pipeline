#include "ExchangeType.hpp"

Exchange ExchangeType::toExchange(const std::string& str) {
    const char  *exchange_1 = DATA::EXCHANGE_1, 
                *exchange_2 = DATA::EXCHANGE_2;

    if (!exchange_1) 
        RUNTIME_ERROR("Environment variable EXCHANGE_1 is not set");

    if (!exchange_2) 
        RUNTIME_ERROR("Environment variable EXCHANGE_2 is not set");

    if (exchange_1 && str == exchange_1)
        return Exchange::EXCHANGE_1;

    if (exchange_2 && str == exchange_2)
        return Exchange::EXCHANGE_2;

    return Exchange::UNKNOWN;
}


Type ExchangeType::toType(const std::string& str) {
    if (str == DATA::OPTION) return Type::OPTION;
    if (str == DATA::FUTURE) return Type::FUTURE;
    if (str == DATA::EQUITY) return Type::EQUITY;
    return Type::UNKNOWN;
}
