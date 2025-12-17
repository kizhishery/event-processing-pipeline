#pragma once
#include <string>
#include <memory>
#include "../Enums/Enums.hpp"

class Instrument;

class FilterClass {
private:
    Exchange exchangeEnum = Exchange::UNKNOWN;
    Type     typeEnum     = Type::UNKNOWN;

    // 🔥 entire try-catch lives here
    static std::pair<Exchange, Type> parseJsonSafe(const std::string& jsonStr);

public:
    explicit FilterClass(const std::string& jsonStr);

    bool match(Exchange ex, Type ty) const;
    std::unique_ptr<Instrument> getInstrument() const;
};
