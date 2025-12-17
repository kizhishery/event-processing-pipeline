#pragma once
#include <memory>
#include "../Enums/Enums.hpp"
#include "Option.hpp"
#include "Future.hpp"
#include "Equity.hpp"

class InstrumentFactory {
public:
    static std::unique_ptr<Instrument>
    create(Exchange ex, Type type) {

        switch (type) {
            case Type::OPTION:
                return std::make_unique<Option>(ex);
            case Type::FUTURE:
                return std::make_unique<Future>(ex);
            case Type::EQUITY:
                return std::make_unique<Equity>(ex);
            default:
                return nullptr;
        }
    }
};
