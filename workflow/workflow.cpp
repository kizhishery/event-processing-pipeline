#include <iostream>

#include "workflow.hpp"
#include "process/process.hpp"
#include "postJson/postJson.hpp"

void Workflow::execute(const json& record) const
{
    try {
        json data = process(record);
        postJson(data);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing record: " << e.what() << "\n";
    }
}
