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
    BOOST_TEST((c == Config()));
    
    // String
    c = "Hello";
    BOOST_TEST(c == "Hello");
    BOOST_TEST(c == String("Hello"));
    BOOST_TEST(c == Config("Hello"));
    BOOST_TEST(c != "world");
    BOOST_TEST(c != Config("world"));
    
    c = String("World");
    BOOST_TEST(c == "World");
    BOOST_TEST(c == Config("World"));
    BOOST_TEST(c == String("World"));
    BOOST_TEST(c != "hello");
    BOOST_TEST(c != Config("hello"));
    
    // Bool
    c = false;
    BOOST_TEST(c == false);
    BOOST_TEST(c == Config(false));
    BOOST_TEST(c != true);
    BOOST_TEST(c != Config(true));
    
    c = true;
    BOOST_TEST(c == true);
    BOOST_TEST(c == Config(true));
    BOOST_TEST(c != false);
    BOOST_TEST(c != Config(false));
    
    // Int
    c = 10;
    BOOST_TEST(c == 10);
    BOOST_TEST(c == Config(10));
    BOOST_TEST(c != 20);
    BOOST_TEST(c != Config(20));
    
    // Double
    c = 3.14;
    BOOST_TEST(c == 3.14);
    BOOST_TEST(c == Config(3.14));
    BOOST_TEST(c != 6.28);
    BOOST_TEST(c != Config(6.28));
    
    // Map
    c = Config::Map{{"key", 10}};
    BOOST_TEST((c == Config::Map{{"key", 10}}));
    BOOST_TEST((c == Config(Config::Map{{"key", 10}})));
    BOOST_TEST((c != Config::Map{{"key", 20}}));
    BOOST_TEST((c != Config(Config::Map{{"key", 20}})));
    
    // Array
    c = Config::Array{1, false, "Hi"};
    BOOST_TEST((c == Config::Array{1, false, "Hi"}));
    BOOST_TEST((c == Config(Config::Array{1, false, "Hi"})));
    BOOST_TEST((c != Config::Array{1, true, "Hi"}));
    BOOST_TEST((c != Config(Config::Array{1, true, "Hi"})));
    
    // nullptr
    BOOST_TEST((c != nullptr));
    BOOST_TEST((c != Config(nullptr)));
    
    // Config equality
    Config c1, c2;
    BOOST_TEST(c1 == c2);
    
    c1 = 10;
    BOOST_TEST(c1 != c2);
    
    c2 = 10;
    BOOST_TEST(c1 == c2);
    
    Config c3{c2};
    BOOST_TEST(c3 == c2);
}
