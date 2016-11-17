//
//  Config.hpp
//  cpp-test
//
//  Created by Albert on 28/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#pragma once
#include "Utils.hpp"

#define FBIDE_CONFIG_VAL_TYPES  String, bool, int, double
#define FBIDE_CONFIG_TYPES      std::nullptr_t, FBIDE_CONFIG_VAL_TYPES, Array, Map

//
// Goal:
// - easy to use
// - const correct
// - reference semantics
// - option for deep copy
// - extendable. One config tree extends another and defaults to "parent"
//   tree if value doesn't exist
// - typed map and array iterators
//

namespace fbide {
    
    class Config final
    {
    public:
        
        using Map   = StringMap<Config>;
        using Array = std::vector<Config>;
        
        /**
         * Types of values that Config can hold
         */
        enum class Type
        {
            Null, String, Bool, Int, Double, Array, Map
        };
        
        
        /**
         * By default Config will hold null value
         */
        Config() :                         m_val(std::make_shared<Storage>(nullptr)) {}
        Config(std::nullptr_t) :           Config() {}
        Config(const Config & other) :     m_val(other.m_val) {}
        Config(Config && other) noexcept : m_val(std::move(other.m_val)) {}
        
        // String
        Config(const char * value) :      m_val(std::make_shared<Storage>(String{value})) {}
        Config(const String & value) :    m_val(std::make_shared<Storage>(value)) {}
        Config(String && value) noexcept: m_val(std::make_shared<Storage>(std::move(value))) {}
        
        // Bool
        Config(bool value) : m_val(std::make_shared<Storage>(value)) {}
        
        // Int
        Config(int value) : m_val(std::make_shared<Storage>(value)) {}
        
        // Double
        Config(double value) : m_val(std::make_shared<Storage>(value)) {}

        // Array
        Config(const Array & value) :    m_val(std::make_shared<Storage>(value)) {}
        Config(Array && value) noexcept: m_val(std::make_shared<Storage>(std::move(value))) {}

        // Map
        Config(const Map & value) :    m_val(std::make_shared<Storage>(value)) {}
        Config(Map && value) noexcept: m_val(std::make_shared<Storage>(std::move(value))) {}
        
        //----------------------------------------------------------------------
        // Get values
        //----------------------------------------------------------------------
        
        inline const optional<String> GetString() const { return Get<String>(); }
        
        inline const optional<bool> GetBool() const { return Get<bool>(); }
        
        inline const optional<int> GetInt() const { return Get<int>(); }
        
        inline const optional<double> GetDouble() const { return Get<double>(); }
        
        inline const optional<Array> GetArray() const { return Get<Array>(); }
        
        inline const optional<Map> GetMap() const { return Get<Map>(); }
        
        template<typename T, typename = std::enable_if<is_one_of<T, FBIDE_CONFIG_TYPES>()>>
        inline const optional<T> Get() const
        {
            if (m_val->type() == typeid(T)) {
                return optional<T>{boost::get<T>(*m_val)};
            }
            return {};
        }
        
        template<typename T, typename = std::enable_if<is_one_of<T, FBIDE_CONFIG_VAL_TYPES>()>>
        inline const optional<std::vector<T>> AsArray() const
        {
            if (!IsArray()) {
                return {};
            }
            auto res = make_optional(std::vector<T>());
            for (auto & value : boost::get<Array&>(*m_val)) {
                if (value.m_val->type() == typeid(T)) {
                    res->emplace_back(boost::get<T>(*value.m_val));
                }
            }
            return res;
        }
        
        
        //----------------------------------------------------------------------
        // Query value type
        //----------------------------------------------------------------------
        
        
        String GetTypeName() const;
        inline Type GetType()  const { return (Type)m_val->which(); }
        inline bool IsNull()   const { return GetType() == Type::Null; }
        inline bool IsString() const { return GetType() == Type::String; }
        inline bool IsBool()   const { return GetType() == Type::Bool; }
        inline bool IsInt()    const { return GetType() == Type::Int; }
        inline bool IsDouble() const { return GetType() == Type::Double; }
        inline bool IsArray()  const { return GetType() == Type::Array; }
        inline bool IsMap()    const { return GetType() == Type::Map; }
        
    private:
        
        using Storage   = boost::variant<FBIDE_CONFIG_TYPES>;
        using Container = std::shared_ptr<Storage>;
        
        Container m_val;
    };
    
    /**
     * Print the type to the stream
     */
    std::ostream& operator << (std::ostream& stream, const Config::Type& type);
}
