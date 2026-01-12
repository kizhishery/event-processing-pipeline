#include "equity.hpp"

json Equity::process(const json& jsonData) {
    
    switch (exchange) {
        case Exchange::EXCHANGE_1:
            return processEquityExchangeOne(jsonData,DATA::EXCHANGE_1);

        case Exchange::EXCHANGE_2:
            return processEquityExchangeTwo(jsonData,DATA::EXCHANGE_2);

        default:
            return json{};
    }
}

json Equity::processEquityExchangeOne(const json& jsonData,const std::string& exchange) {
    json result;

    const std::string timeStr = jsonData.value("time", "");

    if (!jsonData.contains("data") || jsonData["data"].empty()) {
        RUNTIME_ERROR("data val is missing");
        return result;
    }
    
    const auto& dataArray = jsonData["data"][0];
    const auto& data      = dataArray["data"];
    
    for (const auto& val : data) {
        if(val.value("priority",0) != 1)
        continue;
        
        result[EQUITY::KEY]                 = val.value("symbol", "") + " | " + timeStr.substr(0,timeStr.find("T"));
        result[EQUITY::TYPE]                = DATA::EQUITY;
        result[EQUITY::VOLUME]              = val.value("totalTradedVolume", 0);
        result[EQUITY::EXCHANGE]            = exchange;
        result[EQUITY::TIMESTAMP]           = timeStr;
        result[EQUITY::UNDERLYING]          = val.value("symbol", "");
        result[EQUITY::PREVIOUS_CLOSE]      = val.value("previousClose", 0.0);
        result[EQUITY::LAST_TRADED_PRICE]   = val.value("lastPrice", 0.0);
        
        break;
    }
    
    return result;
}

json Equity::processEquityExchangeTwo(const json& jsonData,const std::string& exchange) {
    json result;
    
    const std::string timeStr = jsonData.value("time", "");
    
    if (!jsonData.contains("data") || jsonData["data"].empty()) {
        RUNTIME_ERROR("data val is missing");
        return result;
    }
    
    const auto& dataArray = jsonData["data"][0];
    const auto& data      = dataArray["data"];
    
    for (const auto& val : data) {
        if(val.value("priority",0) != 1)
        continue;
        
        result[EQUITY::KEY]                 = val.value("symbol", "") + " | " + timeStr.substr(0,timeStr.find("T"));
        result[EQUITY::TYPE]                = DATA::EQUITY;
        result[EQUITY::VOLUME]              = val.value("totalTradedVolume", 0);
        result[EQUITY::EXCHANGE]            = exchange;
        result[EQUITY::TIMESTAMP]           = timeStr;
        result[EQUITY::UNDERLYING]          = val.value("symbol", "");
        result[EQUITY::PREVIOUS_CLOSE]      = val.value("previousClose", 0.0);
        result[EQUITY::LAST_TRADED_PRICE]   = val.value("lastPrice", 0.0);
        
        break;
    }

    return result;
}

