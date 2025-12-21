#include <iostream>
#include <fstream>
#include <vector>
#include "../nlohmann/json.hpp"
#include "future.hpp"
#include "option.hpp"

using json = nlohmann::json;

json load_json(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open: " + path);

    json data;
    file >> data;
    return data;
}

struct Job {
    std::string file;
    json (*processor)(const json&);
};

int main() {
    try {
        std::vector<Job> jobs = {
            // {"data/nse_future.json", &Future::processFutureNSE},
            // {"data/bse_future.json", &Future::processFutureBSE},
            {"data/nse_option.json", &Option::processOptionNSE},
            // {"data/bse_option.json", &Option::processOptionBSE},
        };

        for (const auto& job : jobs) {
            json input  = load_json(job.file);
            json output = job.processor(input);

            // derive output file name
            std::string outFile = job.file;
            outFile.replace(outFile.find(".json"), 5, "_out.json");

            std::ofstream ofs(outFile);
            if (!ofs.is_open()) {
                throw std::runtime_error("Failed to open output file: " + outFile);
            }

            ofs << output.dump(4);
            ofs.close();
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
