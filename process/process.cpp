#include "process.hpp"


json process(const json& record){
    try {
        // LOG_JSON(record,4);
        // SQS body
        if (!record.contains("body") || !record["body"].is_string()) {
            RUNTIME_ERROR("record missing body parameter");
            return json::object();
        }
        
        json sqsBody = json::parse(record["body"].get<std::string>());
        
        // Sqs Message 
        if (!sqsBody.contains("Message") || !sqsBody["Message"].is_string()) {
            RUNTIME_ERROR("record missing Message parameter");
            return json::object();
        }
        
        json messages = json::parse(sqsBody["Message"].get<std::string>());
        // Validate Buffer payload
        if (!messages.contains("type") || messages["type"] != "Buffer" || !messages.contains("data") || !messages["data"].is_array()){
            RUNTIME_ERROR("record missing type | data");
            return json::object();
        }

        // Extract gzip buffer
        std::vector<unsigned char> zipArray;
        zipArray.reserve(messages["data"].size());

        for (const auto& message : messages["data"])
            zipArray.push_back(message.get<unsigned char>());

        // Decompress gzip → JSON
        json decompressedJSON = readGzippedJson(zipArray);

        // Filter → Instrument
        FilterClass filter(decompressedJSON);
        std::unique_ptr<Instrument> instrument = filter.getInstrument();

        if (!instrument) {
            RUNTIME_ERROR("Unable to find instrument");
            return json::object();
        }
        // Final processed output
        return instrument -> process(decompressedJSON);
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());
        return json::object();
    }
}
