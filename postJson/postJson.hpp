#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "macro/logger.hpp"
#include "namespace/data.hpp"

using json = nlohmann::json;

// Sends JSON payload via HTTP POST
void postJson(const json& payload);
