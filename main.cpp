#include <iostream>
#include "Instrument/Instrument.hpp"
#include "FilterClass/FilterClass.hpp"

int main() {
    std::string jsonStr1 = R"({"exchange": "EXCHANGE_2", "type": "EQUITY", "data" : []})",
                jsonStr2 = R"({"exchange": "EXCHANGE_2", "type": "EQUITY", "data" : []})",
                jsonStr3 = R"({"exchange": "EXCHANGE_1", "type": "OPTION", "data" : []})";

    FilterClass f1(jsonStr1), f2(jsonStr2), f3(jsonStr3);

    auto instrument_1 = f1.getInstrument(), 
         instrument_2 = f2.getInstrument(),
         instrument_3 = f3.getInstrument();

    if (instrument_1) instrument_1->log();
    if (instrument_2) instrument_2->log();
    if (instrument_3) instrument_3->log();
}
