#include <aws/lambda-runtime/runtime.h>

#include "environment/lambda.hpp"

int main()
{
    aws::lambda_runtime::run_handler(lambda_handler);
    return 0;
}
