#include "process.hpp"

#include <memory>
#include <vector>
#include <iostream>

#include <nlohmann/json.hpp>

#include "utils/gzip_json.hpp"
#include "instrument/instrument.hpp"
#include "filterclass/filterclass.hpp"

using json = nlohmann::json;

json process(const json& record){
    try {
        std::cout<<record.dump()<<'\n';
        // ----------------------------
        // 1. SQS body (STRING)
        // ----------------------------
        if (!record.contains("body") || !record["body"].is_string()) {
            std::cout<<"record missing body parameter"<<'\n';
            return json::object();
        }
        
        json snsBody = json::parse(record["body"].get<std::string>());
        
        // ----------------------------
        // 2. SNS Message (STRING)
        // ----------------------------
        if (!snsBody.contains("Message") || !snsBody["Message"].is_string()) {
            std::cout<<"record missing Message parameter"<<'\n';
            return json::object();
        }
        
        json messageObj = json::parse(snsBody["Message"].get<std::string>());
        std::cout<<"messageObj"<<messageObj.dump()<<'\n';
        // ----------------------------
        // 3. Validate Buffer payload
        // ----------------------------
        if (!messageObj.contains("type") ||
        messageObj["type"] != "Buffer" ||
        !messageObj.contains("data") ||
        !messageObj["data"].is_array()){
            std::cout<<"record missing type | data"<<'\n';
            return json::object();
        }

        // ----------------------------
        // 4. Extract gzip buffer
        // ----------------------------
        std::vector<unsigned char> zipArray;
        zipArray.reserve(messageObj["data"].size());

        for (const auto& b : messageObj["data"])
            zipArray.push_back(b.get<unsigned char>());

        // ----------------------------
        // 5. Decompress gzip → JSON
        // ----------------------------
        json decompressedJSON = readGzippedJson(zipArray);
        std::cout<<"decompressedJSON"<<decompressedJSON.dump(4)<<'\n';
        // ----------------------------
        // 6. Filter → Instrument
        // ----------------------------
        FilterClass filter(decompressedJSON.dump());
        std::unique_ptr<Instrument> instrument = filter.getInstrument();

        if (!instrument)
            return json::object();

        // instrument->log();

        // ----------------------------
        // 7. Final processed output
        // ----------------------------
        return instrument->process(decompressedJSON);
    }
    catch (const std::exception& e) {
        std::cerr << "[process] Error: " << e.what() << "\n";
        return json::object();
    }
}
