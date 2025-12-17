#pragma once
#include "../Enums/Enums.hpp"

class Instrument {
protected:
    Exchange exchange;

public:
    explicit Instrument(Exchange ex) : exchange(ex) {}
    virtual ~Instrument() = default;

    virtual void log() const = 0;
};
