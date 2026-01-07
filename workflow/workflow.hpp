#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/**
 * Workflow
 * ----------
 * Handles orchestration and error isolation for one record.
 */
class Workflow {
public:
    Workflow() = default;

    // Execute workflow for a single record
    void execute(const json& record) const;
};
