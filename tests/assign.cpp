//
//  assign.cpp
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


BOOST_AUTO_TEST_CASE(assign)
{
    Config c;
    BOOST_TEST(c.IsNull());
    
    // String
    c = "Hello";
    {
        BOOST_TEST(c.IsString());
        auto v = c.GetString();
        BOOST_TEST(*v == "Hello");
    }
    
    c = String("World");
    {
        BOOST_TEST(c.IsString());
        auto v = c.GetString();
        BOOST_TEST(*v == "World");
    }
    
    // Bool
    c = true;
    {
        BOOST_TEST(c.IsBool());
        auto v = c.GetBool();
        BOOST_TEST(*v == true);
    }
    
    c = false;
    {
        BOOST_TEST(c.IsBool());
        auto v = c.GetBool();
        BOOST_TEST(*v == false);
    }
    
    // Int
    c = 10;
    {
        BOOST_TEST(c.IsInt());
        auto v = c.GetInt();
        BOOST_TEST(*v == 10);
    }
    
    // Double
    c = 3.14;
    {
        BOOST_TEST(c.IsDouble());
        auto v = c.GetDouble();
        BOOST_TEST(*v == 3.14);
    }
    
    // Map
    c = Config::Map{{"key", "val"}};
    {
        BOOST_TEST(c.IsMap());
        auto m = c.AsMap<String>();
        BOOST_TEST(m->size() == 1);
        BOOST_TEST((*m)["key"] == "val");
    }
    
    
    // Array
    c = Config::Array{1, 2};
    {
        BOOST_TEST(c.IsArray());
        auto m = c.AsArray<int>();
        BOOST_TEST(m->size() == 2);
        BOOST_TEST((*m)[0] == 1);
        BOOST_TEST((*m)[1] == 2);
    }
    
    // nullptr
    c = nullptr;
    BOOST_TEST(c.IsNull());
}
