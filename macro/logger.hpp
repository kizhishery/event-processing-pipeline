#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <nlohmann/json.hpp>  
// nlohmann::json

namespace logger_utils {
    inline std::string currentTime() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
        return std::string(buf);
    }
}

// Normal log
#define LOG(msg) \
    do { \
        std::cout << "[LOG][" << logger_utils::currentTime() << "] " \
                  << __FILE__ << ":" << __LINE__ << " (" << __func__ << ") " \
                  << msg << std::endl; \
    } while (0)

// Error log
#define LOG_ERR(msg) \
    do { \
        std::cerr << "[ERROR][" << logger_utils::currentTime() << "] " \
                  << __FILE__ << ":" << __LINE__ << " (" << __func__ << ") " \
                  << msg << std::endl; \
    } while (0)

// JSON log with optional indentation
#define LOG_JSON(val, ...) \
    do { \
        std::cout << "[JSON][" << logger_utils::currentTime() << "] " \
                  << __FILE__ << ":" << __LINE__ << " (" << __func__ << ") " \
                  << (val).dump(__VA_ARGS__) << std::endl; \
    } while (0)

#define RUNTIME_ERROR(msg) \
    do { \
        throw std::runtime_error(msg); \
    } while (0)

