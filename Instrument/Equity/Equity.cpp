#include "equity.hpp"

void Equity::log() const {
    if (exchange == Exchange::EXCHANGE_1)
        std::cout << "EXCHANGE_1 EQUITY\n";
    else if (exchange == Exchange::EXCHANGE_2)
        std::cout << "EXCHANGE_2 EQUITY\n";
    else
        std::cout << "UNKNOWN\n";
}

json Equity::processEquityExchangeOne(const json& jsonData) {
    json result;

    const std::string timeStr = jsonData.value("time", "");

    if (!jsonData.contains("data") || jsonData["data"].empty())
        return result;

    const auto& dataArray = jsonData["data"][0];
    const auto& data      = dataArray["data"];

    for (const auto& val : data) {
		if(val.value("priority",0) != 1)
			continue;

        result["ts"]  = timeStr;
        result["key"] = val.value("symbol", "") + " | " + timeStr.substr(0,timeStr.find("T"));
        result["ltp"] = val.value("lastPrice", 0.0);
        result["pc"]  = val.value("previousClose", 0.0);
        result["ul"]  = val.value("symbol", "");
        result["vol"] = val.value("totalTradedVolume", 0);
        break;
    }

    return result;
}