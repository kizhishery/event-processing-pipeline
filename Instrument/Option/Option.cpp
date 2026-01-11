#include "option.hpp"

json Option::process(const json& jsonData) {
    switch (exchange) {
        case Exchange::EXCHANGE_1:
            return processOptionExchangeOne(jsonData);

        case Exchange::EXCHANGE_2:
            return processOptionExchangeTwo(jsonData);

        default:
            return json{};
    }
}

// ---------- ExchangeOne side ----------
json Option::processExchangeOne(const json& side) {
    json Json;

    Json[OPTION::VOLUME]                = side.value("totalTradedVolume", 0);
    Json[OPTION::BUY_PRICE]             = side.value("buyPrice1", 0.0);
    Json[OPTION::SELL_PRICE]            = side.value("sellPrice1", 0.0);
    Json[OPTION::BUY_QUANTITY]          = side.value("buyQuantity1", 0);
    Json[OPTION::SELL_QUANTITY]         = side.value("sellQuantity1", 0);
    Json[OPTION::OPEN_INTEREST]         = side.value("openInterest", 0);
    Json[OPTION::LAST_TRADED_PRICE]     = side.value("lastPrice", 0.0);
    Json[OPTION::IMPLIED_VOLATILITY]    = std::round(side.value("impliedVolatility", 0.0) * 100.0) / 100.0;
    Json[OPTION::TOTAL_BUY_QUANTITY]    = side.value("totalBuyQuantity", 0);
    Json[OPTION::TOTAL_SELL_QUANTITY]   = side.value("totalSellQuantity", 0);
    
    return Json;
}

// ---------- ExchangeTwo side ----------
json Option::processExchangeTwo(const json& side, bool isCE) {
    json Json;
    const std::string p = isCE ? "C_" : "";

    Json[OPTION::VOLUME]                = toInt   (side, (p + "Vol_Traded").c_str());
    Json[OPTION::BUY_PRICE]             = toDouble(side, (p + "BidPrice").c_str());
    Json[OPTION::SELL_PRICE]            = toDouble(side, (p + "OfferPrice").c_str());
    Json[OPTION::BUY_QUANTITY]          = toInt   (side, (p + "BIdQty").c_str());
    Json[OPTION::SELL_QUANTITY]         = toInt   (side, (p + "OfferQty").c_str());
    Json[OPTION::OPEN_INTEREST]         = toInt   (side, (p + "Open_Interest").c_str());
    Json[OPTION::LAST_TRADED_PRICE]     = toDouble(side, (p + "Last_Trd_Price").c_str());
    Json[OPTION::IMPLIED_VOLATILITY]    = std::round(toDouble(side, (p + "IV").c_str()) * 100.0) / 100.0;
    Json[OPTION::TOTAL_BUY_QUANTITY]    = toInt   (side, (p + "BIdQty").c_str());
    Json[OPTION::TOTAL_SELL_QUANTITY]   = toInt   (side, (p + "OfferQty").c_str());
    
    return Json;
}

// ---------- Common option builder ----------
json Option::buildOption(
    int strike,
    double underlyingValue,
    const std::string& timestamp,
    const std::string& underlying,
    const std::string& expiry,
    const json& ce,
    const json& pe
) {
    json option;
    
    option[OPTION::CE]  = ce;
    option[OPTION::PE]  = pe;
    option[OPTION::KEY] = std::to_string(strike) + " | " + expiry;
    option[OPTION::EXPIRY] = expiry;
    option[OPTION::TIMESTAMP]  = timestamp;
    option[OPTION::UNDERLYING]  = underlying;
    option[OPTION::STRIKE_PRICE] = strike;
    option[OPTION::UNDERLYING_VALUE] = underlyingValue;

    return option;
}


// ---------- Strike bounds ----------
std::pair<int, int> Option::calculateBound(double underlyingValue, int multiplier, int count) {
    int base = static_cast<int>(underlyingValue);
    return { base - multiplier * count, base + multiplier * count };
}

// ---------- Safe parsers ----------
double Option::toDouble(const json& j, const char* key) {
    if (!j.contains(key))
        return 0.0;

    std::string s = j.value(key, "");
    if (s.empty())
        return 0.0;

    std::string clean;
    for (char c : s)
        if (c != ',')
            clean += c;

    return std::stod(clean);
}

int Option::toInt(const json& j, const char* key) {
    return static_cast<int>(toDouble(j, key));
}

// ---------- ExchangeOne option chain ----------
json Option::processOptionExchangeOne(const json& jsonData) {
    json result = json::array();
    // LOG_JSON(result,4);

    if (!jsonData.contains("data") || !jsonData["data"].is_array()) {
        RUNTIME_ERROR("data val arg is missing");
        return result;
    }
    
    const std::string ts = jsonData.value("time", "");
    
    for (const auto& block : jsonData["data"]) {
        
        if (!block.contains("records")) {
            RUNTIME_ERROR("record arg val is missing");
            continue;
        }
        const auto& records = block["records"];
        
        if (!records.contains("data")) {
            RUNTIME_ERROR("data arg val is missing");
            continue;
        }
        
        double ulv = records.value("underlyingValue", 0.0);
        auto [low, high] = calculateBound(ulv, 50, 10);
        
        for (const auto& row : records["data"]) {
            int strike = row.value("strikePrice", 0);
            if (strike < low || strike > high)
            continue;
            
            result.push_back(
                buildOption(
                    strike,
                    ulv,
                    ts,
                    row.value("CE", json::object()).value("underlying", ""),
                    row.value("expiryDates", ""),
                    processExchangeOne(row.value("CE", json::object())),
                    processExchangeOne(row.value("PE", json::object()))
                )
            );
        }
    }
    
    return result;
}

// ---------- ExchangeTwo option chain ----------
json Option::processOptionExchangeTwo(const json& jsonData) {
    json result = json::array();
    
    if (!jsonData.contains("data") || !jsonData["data"].is_array()) {
        RUNTIME_ERROR("data val arg is missing");
        return result;
    }
    
    const std::string ts = jsonData.value("time", "");
    
    for (const auto& block : jsonData["data"]) {
        
        if (!block.contains("Table")) {
            RUNTIME_ERROR("Table val arg is missing");
            continue;
        }
        const auto& table = block["Table"];
        
        double ulv = 0.0;
        for (const auto& r : table) {
            ulv = toDouble(r, "UlaValue");
            if (ulv > 0) break;
        }
        if (ulv == 0) continue;
        
        auto [low, high] = calculateBound(ulv, 100, 10);
        
        for (const auto& row : table) {
            int strike = toInt(row, "Strike_Price");
            if (strike < low || strike > high)
            continue;
            
            result.push_back(
                buildOption(
                    strike,
                    ulv,
                    ts,
                    row.value("Ula_Code", ""),
                    row.value("End_TimeStamp", ""),
                    processExchangeTwo(row, true),
                    processExchangeTwo(row, false)
                )
            );
        }
    }

    return result;
}