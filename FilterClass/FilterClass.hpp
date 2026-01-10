#pragma once

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

#include "../Enums/Enums.hpp"
#include "../ExchangeType/ExchangeType.hpp"
#include "../Instrument/InstrumentFactory.hpp"

using json = nlohmann::json;

class FilterClass {
private:
    Type typeEnum = Type::UNKNOWN;
    Exchange exchangeEnum = Exchange::UNKNOWN;

    // 🔥 entire try-catch lives here
    static std::pair<Exchange, Type> parseJson(const json& jsonStr);

public:
    explicit FilterClass(const json& Json);

    bool match(Exchange exchange, Type type) const;
    std::unique_ptr<Instrument> getInstrument() const;
};
