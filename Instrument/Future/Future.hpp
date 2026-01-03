#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "../Instrument.hpp"

using json = nlohmann::json;

class Future : public Instrument {
public:
    explicit Future(Exchange exchange) : Instrument(exchange) {}

    void log() const override;
    json process(const json& jsonData) override;

    static json processFutureExchangeOne(const json& jsonData);
    static json processFutureExchangeTwo(const json& jsonData);
};

