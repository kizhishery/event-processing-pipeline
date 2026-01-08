#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Sends JSON payload via HTTP POST
void postJson(const json& payload);
