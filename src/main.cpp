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

    Config val{"Hello"};
    
    if (auto v = val.Get<bool>()) {
        *v = true;
    }
    
    if (auto v = val.Get<bool>()) {
        std::cout << "v = " << *v << '\n';
    }
    
    if (auto s = val.GetString()) {
        std::cout << "s = " << *s << '\n';
    }
        
    std::cout << "val type is " << val.GetTypeName() << '\n';
    
    return 0;
}
