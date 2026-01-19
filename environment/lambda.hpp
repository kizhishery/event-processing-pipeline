#pragma once

#include <iostream>

#include "nlohmann/json.hpp"
#include "processworkflow.hpp"
#include "macro/logger.hpp"
#include "aws/lambda-runtime/runtime.h"

using namespace aws::lambda_runtime;

inline invocation_response lambda(invocation_request const& request)
{
    std::cout<<"running from lambda"<<'\n';
    try {
        json root = json::parse(request.payload);
        processWorkFlow(root);

        return invocation_response::success(
            "OK",
            "application/json"
        );
    }
    catch (const std::exception& e) {
        LOG_ERR(e.what());
        return invocation_response::failure(
            e.what(),
            "application/json"
        );
    }
}
