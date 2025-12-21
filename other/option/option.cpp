#include "option.hpp"

// ---------- Common NSE side processing ----------
json Option::processNSE(const json& side) {
    json Json;
    Json["ltp"] = side.value("lastPrice", 0.0);
    Json["bp"]  = side.value("buyPrice1", 0.0);
    Json["sp"]  = side.value("sellPrice1", 0.0);
    Json["oi"]  = side.value("openInterest", 0);
    Json["bq"]  = side.value("buyQuantity1", 0);
    Json["sq"]  = side.value("sellQuantity1", 0);
    Json["tbq"] = side.value("totalBuyQuantity", 0);
    Json["tsq"] = side.value("totalSellQuantity", 0);
    Json["vol"] = side.value("totalTradedVolume", 0);
    Json["iv"]  = side.value("impliedVolatility", 0.0);
    return Json;
}

// ---------- Strike bounds ----------
std::pair<int, int>
Option::calculateBound(double underlyingValue, int multiplier, int count) {
    const int base = static_cast<int>(underlyingValue);
    return { base - multiplier * count, base + multiplier * count };
}

// ---------- NSE Option Chain ----------
json Option::processOptionNSE(const json& jsonData) {
    json result = json::array();

    if (!jsonData.contains("data") || !jsonData["data"].is_array())
        return result;

    const std::string timestamp = jsonData.value("time", "");

    for (const auto& block : jsonData["data"]) {

        if (!block.contains("records") || !block["records"].is_object())
            continue;

        const auto& records = block["records"];
        if (!records.contains("data") || !records["data"].is_array())
            continue;

        const double underlyingValue = records.value("underlyingValue", 0.0);
        auto [lowerLimit, upperLimit] =
            calculateBound(underlyingValue, 50, 10);

        for (const auto& val : records["data"]) {

            const int strike = val.value("strikePrice", 0);
            if (strike < lowerLimit || strike > upperLimit)
                continue;

            json option;

            const json ce = processNSE(val.value("CE", json::object()));
            const json pe = processNSE(val.value("PE", json::object()));

            const std::string expiry = val.value("expiryDates", "");

            option["ts"]  = timestamp;
            option["ul"]  = val.value("CE", json::object())
                                .value("underlying", "");
            option["ulv"] = underlyingValue;
            option["exp"] = expiry;
            option["str"] = strike;
            option["key"] = std::to_string(strike) + " | " + expiry;
            option["ce"]  = ce;
            option["pe"]  = pe;

            result.push_back(option);
        }
    }

    return result;
}

// ---------- BSE Option Chain ----------
json Option::processOptionBSE(const json& jsonData) {
    json result = json::array();

    if (!jsonData.contains("data") || !jsonData["data"].is_array())
        return result;

    const std::string timestamp = jsonData.value("time", "");

    for (const auto& block : jsonData["data"]) {

        if (!block.contains("records"))
            continue;

        const auto& records = block["records"];
        if (!records.contains("data") || !records["data"].is_array())
            continue;

        const double underlyingValue =
            records.value("underlyingValue", 0.0);

        for (const auto& val : records["data"]) {

            const int strike = val.value("strikePrice", 0);
            json option;

            const json ce = processNSE(val.value("CE", json::object()));
            const json pe = processNSE(val.value("PE", json::object()));

            const std::string expiry = val.value("expiryDates", "");

            option["ts"]  = timestamp;
            option["ulv"] = underlyingValue;
            option["exp"] = expiry;
            option["str"] = strike;
            option["key"] = std::to_string(strike) + " | " + expiry;
            option["ce"]  = ce;
            option["pe"]  = pe;

            result.push_back(option);
        }
    }

    return result;
}
