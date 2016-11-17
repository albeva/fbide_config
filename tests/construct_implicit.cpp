//
//  construct_implicit.cpp
//  fbide_config
//
//  Created by Albert on 29/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//

#include <iostream>
#include "Utils.hpp"
#include "Config.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace fbide;


Config::Type foo(const Config & config)
{
    return config.GetType();
}


BOOST_AUTO_TEST_CASE(construct_implicit_config)
{
    // default
    {
        BOOST_TEST(foo({}) == Config::Type::Null);
    }
    // nullptr
    {
        BOOST_TEST(foo(nullptr) == Config::Type::Null);
    }
    // const char *
    {
        BOOST_TEST(foo("hello") == Config::Type::String);
    }
    // String
    {
        String s = "hello";
        BOOST_TEST(foo(s) == Config::Type::String);
    }
    // bool true
    {
        BOOST_TEST(foo(true) == Config::Type::Bool);
    }
    // bool false
    {
        BOOST_TEST(foo(false) == Config::Type::Bool);
    }
    // int 0
    {
        BOOST_TEST(foo(0) == Config::Type::Int);
    }
    // int 1
    {
        BOOST_TEST(foo(1) == Config::Type::Int);
    }
    // int var
    {
        int i = 10;
        BOOST_TEST(foo(i) == Config::Type::Int);
    }
    // double 0.0
    {
        BOOST_TEST(foo(0.0) == Config::Type::Double);
    }
    // double 1.0
    {
        BOOST_TEST(foo(1.0) == Config::Type::Double);
    }
    // double var
    {
        double d = 1.0;
        BOOST_TEST(foo(d) == Config::Type::Double);
    }
}
