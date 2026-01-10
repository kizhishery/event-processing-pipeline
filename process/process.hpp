#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "utils/gzip_json.hpp"
#include "instrument/instrument.hpp"
#include "filterclass/filterclass.hpp"

using json = nlohmann::json;

/**
 * Executes full business logic for a single record.
 * Throws on failure.
 */
json process(const json& record);
