#pragma once

#include <vector>
#include <zlib.h>
#include <sstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

#include "macro/logger.hpp" 


using json = nlohmann::json;

json readGzippedJson(const std::vector<unsigned char>& data);
