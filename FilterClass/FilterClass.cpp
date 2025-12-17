#include "FilterClass.hpp"
#include "../ExchangeType/ExchangeType.hpp"
#include "../Instrument/InstrumentFactory.hpp"
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

FilterClass::FilterClass(const std::string& jsonStr) {
    auto [exchange, type] = parseJsonSafe(jsonStr);
    exchangeEnum = exchange, typeEnum = type;
}

std::pair<Exchange, Type> FilterClass::parseJsonSafe(const std::string& jsonStr) {
    try {
        json j = json::parse(jsonStr);

        return {
            ExchangeType::toExchange(j.value("EXCHANGE", "")),
            ExchangeType::toType(j.value("TYPE", ""))
        };
    }
    catch (...) {
        return { Exchange::UNKNOWN, Type::UNKNOWN };
    }
}

bool FilterClass::match(Exchange ex, Type ty) const {
    return exchangeEnum == ex && typeEnum == ty;
}

std::unique_ptr<Instrument>
FilterClass::getInstrument() const {
    return InstrumentFactory::create(exchangeEnum, typeEnum);
}
