//
//  construct.cpp
//  cpp-test
//
//  Created by Albert on 28/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#include <iostream>
#include "Utils.hpp"
#include "Config.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace fbide;

BOOST_AUTO_TEST_CASE(construct_config)
{
    // default
    {
        Config cfg;
        BOOST_TEST(cfg.IsNull());
        BOOST_TEST(cfg.GetType() == Config::Type::Null);
        BOOST_TEST(cfg.GetTypeName() == "null");
    }
    // nullptr
    {
        Config cfg{nullptr};
        BOOST_TEST(cfg.IsNull());
        BOOST_TEST(cfg.GetType() == Config::Type::Null);
        BOOST_TEST(cfg.GetTypeName() == "null");
    }
    // const char *
    {
        Config cfg{"hello"};
        BOOST_TEST(cfg.IsString());
        BOOST_TEST(cfg.GetType() == Config::Type::String);
        BOOST_TEST(cfg.GetTypeName() == "string");
    }
    // String
    {
        Config cfg{String("hello")};
        BOOST_TEST(cfg.IsString());
        BOOST_TEST(cfg.GetType() == Config::Type::String);
        BOOST_TEST(cfg.GetTypeName() == "string");
    }
    // bool true
    {
        Config cfg{true};
        BOOST_TEST(cfg.IsBool());
        BOOST_TEST(cfg.GetType() == Config::Type::Bool);
        BOOST_TEST(cfg.GetTypeName() == "bool");
    }
    // bool false
    {
        Config cfg{false};
        BOOST_TEST(cfg.IsBool());
        BOOST_TEST(cfg.GetType() == Config::Type::Bool);
        BOOST_TEST(cfg.GetTypeName() == "bool");
    }
    // int 0
    {
        Config cfg{0};
        BOOST_TEST(cfg.IsInt());
        BOOST_TEST(cfg.GetType() == Config::Type::Int);
        BOOST_TEST(cfg.GetTypeName() == "int");
    }
    // int 1
    {
        Config cfg{1};
        BOOST_TEST(cfg.IsInt());
        BOOST_TEST(cfg.GetType() == Config::Type::Int);
        BOOST_TEST(cfg.GetTypeName() == "int");
    }
    // int var
    {
        int i = 10;
        Config cfg{i};
        BOOST_TEST(cfg.IsInt());
        BOOST_TEST(cfg.GetType() == Config::Type::Int);
        BOOST_TEST(cfg.GetTypeName() == "int");
    }
    // double 0.0
    {
        Config cfg{0.0};
        BOOST_TEST(cfg.IsDouble());
        BOOST_TEST(cfg.GetType() == Config::Type::Double);
        BOOST_TEST(cfg.GetTypeName() == "double");
    }
    // double 1.0
    {
        Config cfg{1.0};
        BOOST_TEST(cfg.IsDouble());
        BOOST_TEST(cfg.GetType() == Config::Type::Double);
        BOOST_TEST(cfg.GetTypeName() == "double");
    }
    // double var
    {
        double d = 10.0;
        Config cfg{d};
        BOOST_TEST(cfg.IsDouble());
        BOOST_TEST(cfg.GetType() == Config::Type::Double);
        BOOST_TEST(cfg.GetTypeName() == "double");
    }
}
