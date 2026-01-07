#include <fstream>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "workflow/workflow.hpp"

using json = nlohmann::json;

int main() {
    try {
        std::ifstream in("../data.json");
        if (!in)
            throw std::runtime_error("Failed to open ../data.json");

        json root;
        in >> root;

        if (!root.is_array())
            throw std::runtime_error("Expected array of records");

        Workflow workflow;

        for (const auto& record : root) {
            workflow.execute(record);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
