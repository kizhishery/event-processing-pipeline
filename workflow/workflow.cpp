#include "workflow.hpp"

#define logJson(json) std::cout<<"json\n"<<data.dump(4)<<'\n'


void Workflow::execute(const json& record) const
{
    try {
        json data = process(record);
        postJson(data);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing record: " << e.what() << "\n";
    }
}
