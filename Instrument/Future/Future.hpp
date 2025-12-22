#pragma once

#include <iostream>
#include "../Instrument.hpp"
#include "../../nlohmann/json.hpp"

using json = nlohmann::json;

class Future : public Instrument {
public:
    explicit Future(Exchange ex) : Instrument(ex) {}

    void log() const override;

    static json processFutureExchangeOne(const json& jsonData);
    static json processFutureExchangeTwo(const json& jsonData);
};

