//
//  main.cpp
//  cpp-test
//
//  Created by Albert on 28/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#include <iostream>
#include "Utils.hpp"
#include "Config.hpp"
using namespace fbide;


int main(int argc, const char * argv[])
{
    Config c1{10};
    
    if (c1 != "hello") {
        std::cout << "are equal\n";
    } else {
        std::cout << "are not equal\n";
    }
    
    return 0;
}
