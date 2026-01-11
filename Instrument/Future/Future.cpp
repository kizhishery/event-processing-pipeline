#include "future.hpp"

json Future::process(const json& jsonData) {
    switch (exchange) {
        case Exchange::EXCHANGE_1:
            return processFutureExchangeOne(jsonData);

        case Exchange::EXCHANGE_2:
            return processFutureExchangeTwo(jsonData);

        default:
            return json{};
    }
}


json Future::processFutureExchangeOne(const json& jsonData) {
    json result;
    
    const std::string timeStr = jsonData.value("time", "");

    if (!jsonData.contains("data") || jsonData["data"].empty()) {
        RUNTIME_ERROR("data val arg is missing");
        return result;
    }
    
    const auto& dataArray = jsonData["data"][0];
    const auto& data      = dataArray["data"];
    
    for (const auto& val : data) {
        result[FUTURE::KEY]                 = val.value("underlying", "") + " | " + val.value("expiryDate", "");
        result[FUTURE::VOLUME]              = val.value("noOfTrades", 0);
        result[FUTURE::EXPIRY]              = val.value("expiryDate", "");
        result[FUTURE::TIMESTAMP]           = timeStr;
        result[FUTURE::UNDERLYING]          = val.value("underlying", "");
        result[FUTURE::OPEN_INTEREST]       = val.value("openInterest", 0);
        result[FUTURE::TOTAL_TURNOVER]      = val.value("totalTurnover", 0.0) / 1e2;
        result[FUTURE::UNDERLYING_VALUE]    = val.value("underlyingValue", 0.0);
        result[FUTURE::LAST_TRADED_PRICE]   = val.value("lastPrice", 0.0);
        
        break;
    }
    
    return result;
}

json Future::processFutureExchangeTwo(const json& jsonData) {
    json result;
    
    const std::string timeStr = jsonData.value("time", "");
    
    if (!jsonData.contains("data") || jsonData["data"].empty()) {
        RUNTIME_ERROR("data val arg is missing");
        return result;
    }
    
    for (const auto& val : jsonData["data"][0]) {
        const std::string ul =
        val.value("SERIES_CODE", "").substr(0, 6);
        
        result[FUTURE::KEY]                 = ul + " | " + val.value("EXPIRY_OF_CONTRACT", "");
        result[FUTURE::EXPIRY]              = val.value("EXPIRY_OF_CONTRACT", "");
        result[FUTURE::VOLUME]              = val.value("NO_OF_CONTRACTS", 0);
        result[FUTURE::TIMESTAMP]           = timeStr;
        result[FUTURE::UNDERLYING]          = ul;
        result[FUTURE::OPEN_INTEREST]       = val.value("OPEN_INTEREST", 0);
        result[FUTURE::TOTAL_TURNOVER]      = val.value("TURNOVER", 0.0);
        result[FUTURE::UNDERLYING_VALUE]    = val.value("CloseRate", 0.0);
        result[FUTURE::LAST_TRADED_PRICE]   = val.value("LTP", 0.0);
        
        break;
    }

    return result;
}

