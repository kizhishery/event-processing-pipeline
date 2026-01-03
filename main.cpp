#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

#include <nlohmann/json.hpp>
#include "FilterClass/FilterClass.hpp"
#include "Instrument/Instrument.hpp" // Ensure this is included

using json = nlohmann::json;

int main()
{
    try
    {
        std::ifstream in("../data.json");
        if (!in)
        {
            throw std::runtime_error("Failed to open ../data.json");
        }

        json arr;
        in >> arr;

        if (!arr.is_array())
        {
            throw std::runtime_error("Expected JSON array at root");
        }

        for (const auto &msg : arr)
        {
            try
            {
                if (!msg.is_object())
                    continue;

                // 1. Pass the whole object to the Filter (let Filter handle the string conversion if it must)
                std::string input = msg.dump();
                // filter require string unput instead of json object
                FilterClass filter(input);

                std::unique_ptr<Instrument> instrument = filter.getInstrument();

                if (instrument)
                {
                    instrument->log();

                    // 4. Pass this OBJECT to process.
                    // DO NOT use .dump() here if process() expects a json object.
                    json val = instrument->process(msg);
                    std::cout << "Processed Output: " << val.dump(4) << '\n';
                    
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Message-level error: " << e.what() << '\n';
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal system error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}