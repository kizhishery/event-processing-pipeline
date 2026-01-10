#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "../Instrument.hpp"

using json = nlohmann::json;

class Equity : public Instrument {
private:
public:
    explicit Equity(Exchange exchange) : Instrument(exchange) {}
    
    json process(const json& jsonData) override;
    
    static json processEquityExchangeOne(const json& jsonData);
    static json processEquityExchangeTwo(const json& jsonData);
};

