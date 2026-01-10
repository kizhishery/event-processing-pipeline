#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "process/process.hpp"
#include "postJson/postJson.hpp"

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
