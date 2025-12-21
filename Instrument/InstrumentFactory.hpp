#pragma once
#include <memory>
#include "../Enums/Enums.hpp"
#include "Equity/Equity.hpp"
#include "Future/Future.hpp"
#include "Option/Option.hpp"

class InstrumentFactory {
public:
    static std::unique_ptr<Instrument>
    create(Exchange exchange, Type type) {
        switch (type) {
            case Type::OPTION:
                return std::make_unique<Option>(exchange);
            case Type::FUTURE:
                return std::make_unique<Future>(exchange);
            case Type::EQUITY:
                return std::make_unique<Equity>(exchange);
            default:
                return nullptr;
        }
    }
};
