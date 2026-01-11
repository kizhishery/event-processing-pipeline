#include "FilterClass.hpp"

FilterClass::FilterClass(const json& Json) {
    auto [exchange, type] = parseJson(Json);

    exchangeEnum = exchange, typeEnum = type;
}

Pair FilterClass::parseJson(const json& Json) {
    try {
        const std::string type = Json.value("TYPE", "");
        const std::string exchange = Json.value("EXCHANGE", "");

        return Pair(exchange, type);
    }
    catch (const std::runtime_error& err) {
        LOG_ERR(err.what());
        // Uses default constructor
        return Pair(); 
    }
}

bool FilterClass::match(Exchange exchange, Type type) const {
    return exchangeEnum == exchange && typeEnum == type;
}

std::unique_ptr<Instrument> FilterClass::getInstrument() const {
    return InstrumentFactory::create(exchangeEnum, typeEnum);
}
