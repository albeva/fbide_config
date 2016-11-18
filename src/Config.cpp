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


bool Config::operator == (const Config & rhs) const noexcept
{
    if (m_cnt == rhs.m_cnt) {
        return true;
    }
    
    if (GetType() != rhs.GetType()) {
        return false;
    }

    switch(GetType()) {
        case Type::Null:
        {
            return true;
        }
        case Type::String:
        {
            auto & l = as<String>();
            auto & r = rhs.as<String>();
            return l == r;
        }
        case Type::Bool:
        {
            auto & l = as<bool>();
            auto & r = rhs.as<bool>();
            return l == r;
        }
        case Type::Int:
        {
            auto & l = as<int>();
            auto & r = rhs.as<int>();
            return l == r;
        }
        case Type::Double:
        {
            auto & l = as<double>();
            auto & r = rhs.as<double>();
            return l == r;
        }
        case Type::Array:
        {
            auto & l = as<Array>();
            auto & r = rhs.as<Array>();
            return l == r;
        }
        case Type::Map:
        {
            auto & l = as<Map>();
            auto & r = rhs.as<Map>();
            return l == r;
        }
        default:
        {
            return false;
        }
    }
}


String Config::GetTypeName() const noexcept
{
    std::stringstream s;
    s << GetType();
    return s.str();
}
    
    
std::ostream& fbide::operator << (std::ostream& stream, const Config& cfg)
{
    switch(cfg.GetType()) {
    case Config::Type::Null:
        stream << "null";
        break;
    case Config::Type::String:
        stream << *cfg.GetString();
        break;
    case Config::Type::Bool:
        stream << *cfg.GetBool();
        break;
    case Config::Type::Int:
        stream << *cfg.GetInt();
        break;
    case Config::Type::Double:
        stream << *cfg.GetDouble();
        break;
    case Config::Type::Array:
        stream << "[...]";
        break;
    case Config::Type::Map:
        stream << "{...}";
        break;
    }
    return stream;
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
