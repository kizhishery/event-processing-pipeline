#pragma once
#include <iostream>
#include "../Instrument.hpp"
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

class Equity : public Instrument {
private:
public:
    explicit Equity(Exchange exchange) : Instrument(exchange) {}
    
    void log() const override;
    json process(const json& jsonData);
    
    static json processEquityExchangeOne(const json& jsonData);
    static json processEquityExchangeTwo(const json& jsonData);
};

