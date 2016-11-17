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
    Config conf(Config::Array{"Hi", 3, 2.5, false});
    
    if (auto arr = conf.GetArray()) {
        for (auto & c : *arr) {
            std::cout << c.GetTypeName() << '\n';
        }
    }
    
    if (auto arr = conf.AsArray<String>()) {
        for (auto i : *arr) {
            std::cout << "s = " << i << '\n';
        }
    }
        
    Config mcfg{Config::Map{{"key", "val"}, {"lang", "en"}}};
    if (auto map = mcfg.AsMap<String>()) {
        for (auto & entry : *map) {
            std::cout << entry.first << " = " << entry.second << '\n';
        }
    }
    
    return 0;
}
