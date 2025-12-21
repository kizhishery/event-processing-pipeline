#pragma once

#include <string>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

class Option {
public:
	static json processNSE(const json& side) {
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
	static std::pair<int, int> calculateBound(double underlyingValue,int multiplier,int count) {
	    const int base = static_cast<int>(underlyingValue);

	    return std::pair(base - multiplier * count, base + multiplier * count );
	}

	static json processOptionNSE(const json& jsonData) {
		json result = json::array();
		
	    if (!jsonData.contains("data") || !jsonData["data"].is_array())
		return result;
		
	    const std::string timestamp = jsonData.value("time", "");
		
	    for (const auto& block : jsonData["data"]) {
			
			// Skip blocks without valid records
	        if (!block.contains("records") || !block["records"].is_object())
			continue;
			
	        const auto& records = block["records"];
			
	        if (!records.contains("data") || !records["data"].is_array())
			continue;
			
	        const double underlyingValue = records.value("underlyingValue", 0.0);

			auto [lowerLimit,upperLimit] = calculateBound(underlyingValue,50,10);
			
	        for (const auto& val : records["data"]) {
				
				const int strike = val.value("strikePrice", 0);
				if(strike < lowerLimit || upperLimit < strike)
					continue;
				
				json option;
				
	            const json ce = processNSE(val.value("CE", json::object()));
	            const json pe = processNSE(val.value("PE", json::object()));
				
	            const std::string expiry = val.value("expiryDates", "");

	            option["ts"]  = timestamp;
	            option["ul"]  = val.value("CE", json::object()).value("underlying", "");
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

    static json processOptionBSE(const json& jsonData) {
		json result = json::array();
		
        // ---- Top-level guard ----
        if (!jsonData.contains("data") || !jsonData["data"].is_array())
		return result;
		
		const std::string timestamp = jsonData["time"];
        // ---- Loop top-level array ----
        for (const auto& block : jsonData["data"]) {
			
			if (!block.contains("records"))
				continue;
			
            const auto& records = block["records"];
            if (!records.contains("data") || !records["data"].is_array())
				continue;
			
            const double underlyingValue = records.value("underlyingValue", 0.0);

            // ---- REAL option chain loop ----
            for (const auto& val : records["data"]) {
                const int strike = val.value("strikePrice", 0.0);
                json option;

                // ---------- CE ----------
                const auto& CE = val.value("CE", json::object());
                json ce;
                ce["ltp"] = CE.value("lastPrice", 0.0);
                ce["bp"]  = CE.value("buyPrice1", 0.0);
                ce["sp"]  = CE.value("sellPrice1", 0.0);
                ce["oi"]  = CE.value("openInterest", 0);
                ce["bq"]  = CE.value("buyQuantity1", 0);
                ce["sq"]  = CE.value("sellQuantity1", 0);
                ce["tbq"] = CE.value("totalBuyQuantity", 0);
                ce["tsq"] = CE.value("totalSellQuantity", 0);
                ce["vol"] = CE.value("totalTradedVolume", 0);
                ce["iv"]  = CE.value("impliedVolatility", 0.0);
				
                // ---------- PE ----------
                const auto& PE = val.value("PE", json::object());
                json pe;
                pe["ltp"] = PE.value("lastPrice", 0.0);
                pe["bp"]  = PE.value("buyPrice1", 0.0);
                pe["sp"]  = PE.value("sellPrice1", 0.0);
                pe["oi"]  = PE.value("openInterest", 0);
                pe["bq"]  = PE.value("buyQuantity1", 0);
                pe["sq"]  = PE.value("sellQuantity1", 0);
                pe["tbq"] = PE.value("totalBuyQuantity", 0);
                pe["tsq"] = PE.value("totalSellQuantity", 0);
                pe["vol"] = PE.value("totalTradedVolume", 0);
                pe["iv"]  = PE.value("impliedVolatility", 0.0);
				
                // ---------- Common ----------
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
};
