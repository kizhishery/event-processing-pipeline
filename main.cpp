#include <iostream>
#include "environment/local.hpp"

int main() {
    // only runs local workflow
    std::cout<<"running from main.cpp"<<'\n';
    return local(); 
}


