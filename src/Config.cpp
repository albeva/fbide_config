//
//  Config.cpp
//  cpp-test
//
//  Created by Albert on 28/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#include "Config.hpp"
#include <sstream>
using namespace fbide;


String Config::GetTypeName() const
{
    std::stringstream s;
    s << GetType();
    return s.str();
}


std::ostream& fbide::operator << (std::ostream& stream, const Config::Type& type)
{
    switch (type) {
        case Config::Type::Null:
            stream << "null";
            break;
        case Config::Type::String:
            stream << "string";
            break;
        case Config::Type::Bool:
            stream << "bool";
            break;
        case Config::Type::Int:
            stream << "int";
            break;
        case Config::Type::Double:
            stream << "double";
            break;
        case Config::Type::Array:
            stream << "array";
            break;
        case Config::Type::Map:
            stream << "map";
            break;
    }
    return stream;
}
