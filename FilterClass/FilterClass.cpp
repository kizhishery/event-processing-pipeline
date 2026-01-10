#include "FilterClass.hpp"

FilterClass::FilterClass(const json& Json) {
    auto [exchange, type] = parseJson(Json);
    exchangeEnum = exchange, typeEnum = type;
}

std::pair<Exchange, Type> FilterClass::parseJson(const json& Json) {
    try {
        // json Json = json::parse(jsonStr);

        const std::string exchange = Json.value("EXCHANGE",""), value = Json.value("TYPE","");
        return {
            ExchangeType::toExchange(exchange),
            ExchangeType::toType(value)
        };
    }
    catch (...) {
        return { Exchange::UNKNOWN, Type::UNKNOWN };
    }
}

bool FilterClass::match(Exchange exchange, Type type) const {
    return exchangeEnum == exchange && typeEnum == type;
}

std::unique_ptr<Instrument> FilterClass::getInstrument() const {
    return InstrumentFactory::create(exchangeEnum, typeEnum);
}
