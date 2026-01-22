#pragma once

#include <iostream>
#include <exception>
#include <aws/lambda-runtime/runtime.h>

#include "nlohmann/json.hpp"
#include "processworkflow.hpp"
#include "macro/logger.hpp"

inline aws::lambda_runtime::invocation_response lambda_handler(const aws::lambda_runtime::invocation_request& request) {
    std::cout << "running from lambda" << std::endl;

    try {
        nlohmann::json root = nlohmann::json::parse(request.payload);
        // std::cout<<root.dump(4)<<'\n';
        processWorkFlow(root);

        return aws::lambda_runtime::invocation_response::success(
            "OK",
            "application/json"
        );
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());

        return aws::lambda_runtime::invocation_response::failure(
            e.what(),
            "application/json"
        );
    }
}
