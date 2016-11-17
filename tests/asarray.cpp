//
//  asarray.cpp
//  fbide_config
//
//  Created by Albert Varaksin on 17/11/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#include <iostream>
#include "Utils.hpp"
#include "Config.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace fbide;


BOOST_AUTO_TEST_CASE(asarray)
{
    // String
    {
        Config cfg{Config::Array{"Hello", "World", "!"}};
        if (auto arr = cfg.AsArray<String>()) {
            BOOST_TEST(arr->size() == 3);
            BOOST_TEST(arr->at(0) == "Hello");
            BOOST_TEST(arr->at(1) == "World");
            BOOST_TEST(arr->at(2) == "!");
        } else {
            BOOST_TEST_ERROR("Failed to create std::vector<String>");
        }
    }
    // Bool
    {
        Config cfg{Config::Array{true, false, false, true}};
        if (auto arr = cfg.AsArray<bool>()) {
            BOOST_TEST(arr->size() == 4);
            BOOST_TEST(arr->at(0) == true);
            BOOST_TEST(arr->at(1) == false);
            BOOST_TEST(arr->at(2) == false);
            BOOST_TEST(arr->at(3) == true);
        } else {
            BOOST_TEST_ERROR("Failed to create std::vector<bool>");
        }
    }
    // Int
    {
        Config cfg{Config::Array{2, 3, 5, 8}};
        if (auto arr = cfg.AsArray<int>()) {
            BOOST_TEST(arr->size() == 4);
            BOOST_TEST(arr->at(0) == 2);
            BOOST_TEST(arr->at(1) == 3);
            BOOST_TEST(arr->at(2) == 5);
            BOOST_TEST(arr->at(3) == 8);
        } else {
            BOOST_TEST_ERROR("Failed to create std::vector<int>");
        }
    }
    // Double
    {
        Config cfg{Config::Array{1.0, 3.14, 6.28}};
        if (auto arr = cfg.AsArray<double>()) {
            BOOST_TEST(arr->size() == 3);
            BOOST_TEST(arr->at(0) == 1.0);
            BOOST_TEST(arr->at(1) == 3.14);
            BOOST_TEST(arr->at(2) == 6.28);
        } else {
            BOOST_TEST_ERROR("Failed to create std::vector<double>");
        }
    }
}
