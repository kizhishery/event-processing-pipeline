#pragma once
#include <nlohmann/json.hpp>

#include "../Enums/Enums.hpp"

using json = nlohmann::json;
class Instrument {
protected:
    Exchange exchange;

public:
    explicit Instrument(Exchange ex) : exchange(ex) {}
    virtual ~Instrument() = default;
    
    virtual json process(const json& jsonData) = 0;
};
