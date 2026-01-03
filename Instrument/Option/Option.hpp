#pragma once

#include <string>
#include <utility>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../Instrument.hpp"

using json = nlohmann::json;

class Option : public Instrument {
public:
    explicit Option(Exchange exchange) : Instrument(exchange) {}

    void log() const override;

    json process(const json& jsonData) override;
        // ---------- Side processors ----------
    static json processExchangeOne(const json& side);
    static json processExchangeTwo(const json& side, bool isCE);

    // ---------- Option chain ----------
    static json processOptionExchangeOne(const json& jsonData);
    static json processOptionExchangeTwo(const json& jsonData);

    // ---------- Helpers ----------
    static int    toInt(const json& j, const char* key);
    static double toDouble(const json& j, const char* key);
    static std::pair<int, int> calculateBound(double underlyingValue, int multiplier, int count);

    // ---------- Option builder ----------
    static json buildOption(
        int strike,
        double underlyingValue,
        const std::string& timestamp,
        const std::string& underlying,
        const std::string& expiry,
        const json& ce,
        const json& pe
    );
};
