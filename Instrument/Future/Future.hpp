#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "../Instrument.hpp"
#include "../../macro/logger.hpp"
#include "../../namespace/future.hpp"

using json = nlohmann::json;

class Future : public Instrument {
public:
    explicit Future(Exchange exchange) : Instrument(exchange) {}

    json process(const json& jsonData) override;

    static json processFutureExchangeOne(const json& jsonData);
    static json processFutureExchangeTwo(const json& jsonData);
};

