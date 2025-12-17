#pragma once
#include "Instrument.hpp"
#include <iostream>

class Option : public Instrument {
public:
    explicit Option(Exchange ex) : Instrument(ex) {}

    void log() const override {
        if (exchange == Exchange::NSE) std::cout << "NSE-OPTION\n";
        else if (exchange == Exchange::BSE) std::cout << "BSE-OPTION\n";
        else std::cout << "UNKNOWN\n";
    }
};
