#pragma once

#include <string>
#include <memory>
#include <nlohmann/json.hpp>

#include "struct.hpp"

#include "../Enums/Enums.hpp"
#include "../macro/logger.hpp"
#include "../Instrument/InstrumentFactory.hpp"

using json = nlohmann::json;

class FilterClass {
private:
    Type typeEnum = Type::UNKNOWN;
    Exchange exchangeEnum = Exchange::UNKNOWN;

    // 🔥 entire try-catch lives here
    static Pair parseJson(const json& jsonStr);

public:
    explicit FilterClass(const json& Json);

    bool match(Exchange exchange, Type type) const;
    std::unique_ptr<Instrument> getInstrument() const;
};
