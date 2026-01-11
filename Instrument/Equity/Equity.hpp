#pragma once

#include <iostream>

#include "../Instrument.hpp"
#include "../../macro/logger.hpp"
#include "../../namespace/equity.hpp"

class Equity : public Instrument {
private:
public:
    explicit Equity(Exchange exchange) : Instrument(exchange) {}
    
    json process(const json& jsonData) override;
    
    static json processEquityExchangeOne(const json& jsonData);
    static json processEquityExchangeTwo(const json& jsonData);
};

