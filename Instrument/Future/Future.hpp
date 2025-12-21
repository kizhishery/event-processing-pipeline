#pragma once
#include "../Instrument.hpp"
#include <iostream>

class Future : public Instrument {
public:
    explicit Future(Exchange ex) : Instrument(ex) {}

    void log() const override {
        if (exchange == Exchange::NSE) std::cout << "NSE-FUTURE\n";
        else if (exchange == Exchange::BSE) std::cout << "BSE-FUTURE\n";
        else std::cout << "UNKNOWN\n";
    }
};
