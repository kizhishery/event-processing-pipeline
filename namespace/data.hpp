#pragma once
#include <string>
#include <cstdlib>


namespace DATA {
    static constexpr const char* OPTION = "OPTION";
    static constexpr const char* FUTURE = "FUTURE";
    static constexpr const char* EQUITY = "EQUITY";
    
    inline const char* URL = std::getenv("URL");
    inline const char* KEY = std::getenv("KEY");
    inline const char* EXCHANGE_1 = std::getenv("EXCHANGE_1");
    inline const char* EXCHANGE_2 = std::getenv("EXCHANGE_2");
}