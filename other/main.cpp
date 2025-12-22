#include <vector>
#include <future>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "../nlohmann/json.hpp"
#include "future/future.hpp"
#include "option/option.hpp"
#include "equity/equity.hpp"

using json = nlohmann::json;

// ---------------------- Job definition ----------------------
struct Job {
    std::string file;        // input file
    std::string output;      // output file
    json (*processor)(const json&);
};

// ---------------------- JSON loader -------------------------
json load_json(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open input file: " + path);

    json data;
    file >> data;
    return data;
}

// ---------------------- Job runner --------------------------
void run_job(const Job& job) {
    // Load input
    json input = load_json(job.file);

    // Process
    json output = job.processor(input);

    // Ensure output directory exists
    std::filesystem::path outPath(job.output);
    std::filesystem::create_directories(outPath.parent_path());

    // Write output
    std::ofstream ofs(outPath);
    if (!ofs.is_open())
        throw std::runtime_error("Failed to open output file: " + outPath.string());

    ofs << output.dump(4);
}

// ---------------------- Main --------------------------------
int main() {
    try {
        std::vector<Job> jobs {
            {"data/exchange_1_future.json",  "result/exchange_1_future.json",  &Future::processFutureExchangeOne},
            {"data/exchange_2_future.json",  "result/exchange_2_future.json",  &Future::processFutureExchangeTwo},
            {"data/exchange_1_option.json",  "result/exchange_1_option.json",  &Option::processOptionExchangeOne},
            {"data/exchange_2_option.json",  "result/exchange_2_option.json",  &Option::processOptionExchangeTwo},
            {"data/exchange_1_equity.json",  "result/exchange_1_equity.json",  &Equity::processEquityExchangeOne},
        };

        std::vector<std::future<void>> futures;

        // Launch jobs asynchronously
        for (const auto& job : jobs) {
            futures.emplace_back(
                std::async(std::launch::async, run_job, std::cref(job))
            );
        }

        // Wait for all jobs and propagate exceptions
        for (auto& future : futures) 
            future.get();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
