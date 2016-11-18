//
//  equality.cpp
//  fbide_config
//
//  Created by Albert Varaksin on 18/11/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#include <iostream>
#include "Utils.hpp"
#include "Config.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace fbide;


BOOST_AUTO_TEST_CASE(equality)
{
    Config c;
    BOOST_TEST((c == nullptr));
    
    // String
    c = "Hello";
    BOOST_TEST(c == "Hello");
    BOOST_TEST(c == String("Hello"));
    BOOST_TEST(c != "world");
    
    c = String("World");
    BOOST_TEST(c == "World");
    BOOST_TEST(c == String("World"));
    BOOST_TEST(c != "hello");
    
    // Bool
    c = false;
    BOOST_TEST(c == false);
    BOOST_TEST(c != true);
    
    c = true;
    BOOST_TEST(c == true);
    BOOST_TEST(c != false);
    
    // Int
    c = 10;
    BOOST_TEST(c == 10);
    BOOST_TEST(c != 20);
    
    // Double
    c = 3.14;
    BOOST_TEST(c == 3.14);
    BOOST_TEST(c != 6.28);
    
    // Map
    c = Config::Map{{"key", 10}};
    BOOST_TEST((c == Config::Map{{"key", 10}}));
    BOOST_TEST((c != Config::Map{{"key", 20}}));
    
    // Array
    c = Config::Array{1, false, "Hi"};
    BOOST_TEST((c == Config::Array{1, false, "Hi"}));
    BOOST_TEST((c != Config::Array{1, true, "Hi"}));
    
    // nullptr
    BOOST_TEST((c != nullptr));
}
