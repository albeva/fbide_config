//
//  getters.cpp
//  fbide_config
//
//  Created by Albert Varaksin on 01/11/2016.
//  Copyright © 2016 albeva. All rights reserved.
//

#include <iostream>
#include "Utils.hpp"
#include "Config.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using namespace fbide;


BOOST_AUTO_TEST_CASE(getTYPE_methods)
{
    // String
    {
        auto test = "hello";
        Config cfg{test};
        BOOST_TEST((bool)cfg.Get<String>());
        auto val = cfg.GetString();
        BOOST_TEST((bool)val);
        BOOST_TEST(*val == test);
    }
    // bool
    {
        auto test = true;
        Config cfg{test};
        BOOST_TEST((bool)cfg.Get<bool>());
        auto val = cfg.GetBool();
        BOOST_TEST((bool)val);
        BOOST_TEST(*val == test);
    }
    // int
    {
        auto test = 10;
        Config cfg{test};
        BOOST_TEST((bool)cfg.Get<int>());
        auto val = cfg.GetInt();
        BOOST_TEST((bool)val);
        BOOST_TEST(*val == test);
    }
    // double
    {
        auto test = 3.14;
        Config cfg{test};
        BOOST_TEST((bool)cfg.Get<double>());
        auto val = cfg.GetDouble();
        BOOST_TEST((bool)val);
        BOOST_TEST(*val == test);
    }
}
