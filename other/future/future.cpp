#include "future.hpp"

json Future::processFutureNSE(const json& jsonData) {
    json result;

    const std::string timeStr = jsonData.value("time", "");

    if (!jsonData.contains("data") || jsonData["data"].empty())
        return result;

    const auto& dataArray = jsonData["data"][0];
    const auto& data      = dataArray["data"];

    for (const auto& val : data) {
        result["ts"]  = timeStr;
        result["key"] = val.value("underlying", "") + " | " +
                        val.value("expiryDate", "");
        result["exp"] = val.value("expiryDate", "");
        result["ul"]  = val.value("underlying", "");
        result["ltp"] = val.value("lastPrice", 0.0);
        result["oi"]  = val.value("openInterest", 0);
        result["tto"] = val.value("totalTurnover", 0.0) / 1e2;
        result["ulv"] = val.value("underlyingValue", 0.0);
        result["vol"] = val.value("noOfTrades", 0);
        break;
    }

    return result;
}

json Future::processFutureBSE(const json& jsonData) {
    json result;

    const std::string timeStr = jsonData.value("time", "");

    if (!jsonData.contains("data") || jsonData["data"].empty())
        return result;

    for (const auto& val : jsonData["data"]) {
        const std::string ul =
            val.value("SERIES_CODE", "").substr(0, 6);

        result["ts"]  = timeStr;
        result["key"] = ul + " | " +
                        val.value("EXPIRY_OF_CONTRACT", "");
        result["exp"] = val.value("EXPIRY_OF_CONTRACT", "");
        result["ul"]  = ul;
        result["ltp"] = val.value("LTP", 0.0);
        result["oi"]  = val.value("OPEN_INTEREST", 0);
        result["tto"] = val.value("TURNOVER", 0.0);
        result["ulv"] = val.value("CloseRate", 0.0);
        result["vol"] = val.value("NO_OF_CONTRACTS", 0);
        break;
    }

    return result;
}
