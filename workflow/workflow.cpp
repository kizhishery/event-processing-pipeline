#include "workflow.hpp"

#include <iostream>

#include "process/process.hpp"

void Workflow::execute(const json& record) const
{
    try {
        process(record);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing record: " << e.what() << "\n";
    }
}
