#include "FilterClass.hpp"

FilterClass::FilterClass(const std::string& jsonStr) {
    auto [exchange, type] = parseJson(jsonStr);
    exchangeEnum = exchange, typeEnum = type;
}

std::pair<Exchange, Type> FilterClass::parseJson(const std::string& jsonStr) {
    try {
        json Json = json::parse(jsonStr);

        const std::string exchange = Json.value("exchange",""), value = Json.value("type","");
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
