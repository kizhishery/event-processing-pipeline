#pragma once

#include <memory>
#include <future>
#include <vector>
#include <stdexcept>

#include "nlohmann/json.hpp"

#include "macro/logger.hpp"
#include "workflow/workflow.hpp"

using json = nlohmann::json;

inline void processWorkFlow(const json& root) {
    // Expect object instead of array
    if (!root.is_object())
        RUNTIME_ERROR("Expected top-level object");

    if (!root.contains("Records") || !root["Records"].is_array())
        RUNTIME_ERROR("Records array not found");

    auto workflow = std::make_shared<Workflow>();
    std::vector<std::future<void>> futures;

    // Directly iterate Records array
    for (const auto& record : root["Records"]) {
        futures.emplace_back(
            std::async(std::launch::async, [workflow, record]() {
                workflow->execute(record);
            })
        );
    }

    // Wait for all tasks + catch async exceptions
    for (auto& future : futures) {
        try {
            future.get();
        }
        catch (const std::exception& e) {
            LOG_ERR(e.what());
        }
    }
}
