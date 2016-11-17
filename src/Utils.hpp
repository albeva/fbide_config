//
//  Utils.hpp
//  cpp-test
//
//  Created by Albert on 28/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <boost/variant.hpp>
#if __has_include(<optional>)                // Check for a standard library
    #include<optional>
    using std::optional;
    using std::make_optional;
#elif __has_include(<experimental/optional>) // Check for an experimental version
    #include <experimental/optional>
    using std::experimental::optional;
    using std::experimental::make_optional;
#elif __has_include(<boost/optional.hpp>)    // Try with an external library
    #include <boost/optional.hpp>
    using boost::optional;
    using boost::make_optional;
#else                                        // Not found at all
    #error "Missing <optional>"
#endif



namespace fbide {
    
    using String = std::string;
    
    template<class T> using StringMap = std::unordered_map<String, T>;
    
    
    template<typename T> constexpr bool is_one_of()
    {
        return false;
    }
    
    
    template<typename T, typename U, typename... R> constexpr bool is_one_of()
    {
        return std::is_same<std::decay_t<T>, U>::value || is_one_of<T, R...>();
    }
    
}
