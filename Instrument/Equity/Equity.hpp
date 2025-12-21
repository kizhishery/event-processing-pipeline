#pragma once
#include "../Instrument.hpp"
#include <iostream>

class Equity : public Instrument {
public:
    explicit Equity(Exchange exchange) : Instrument(exchange) {}

    void log() const override {
        if (exchange == Exchange::NSE) std::cout << "NSE-EQUITY\n";
        else if (exchange == Exchange::BSE) std::cout << "BSE-EQUITY\n";
        else std::cout << "UNKNOWN\n";
    }
};
