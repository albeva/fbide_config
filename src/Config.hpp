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
#define FBIDE_CONFIG_VAL_ASSIGN std::nullptr_t, bool, int, double

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
        
        
        //----------------------------------------------------------------------
        // Construct, assign (copy, move)
        //----------------------------------------------------------------------
        
        Config(): m_cnt{new Container{nullptr}} {}
        
        Config(std::nullptr_t): Config() {}
        
        Config(const Config & other) noexcept : m_cnt(other.m_cnt)
        {
            m_cnt->m_counter += 1;
        }
        
        Config(Config && other) noexcept : m_cnt(other.m_cnt)
        {
            other.m_cnt = nullptr;
        }
        
        ~Config()
        {
            if (m_cnt == nullptr) {
                return;
            }
            m_cnt->m_counter -= 1;
            if (m_cnt->m_counter == 0) {
                delete m_cnt;
            }
            m_cnt = nullptr;
        }
        
        Config & operator = (const Config & other)
        {
            if (m_cnt != other.m_cnt) {
                m_cnt->m_counter -= 1;
                if (m_cnt->m_counter == 0) {
                    delete m_cnt;
                }
                m_cnt = other.m_cnt;
                m_cnt->m_counter += 1;
            }
            return *this;
        }
        
        Config & operator = (Config && other)
        {
            if (this != &other) {
                m_cnt->m_counter -= 1;
                if (m_cnt->m_counter == 0) {
                    delete m_cnt;
                }
                m_cnt = other.m_cnt;
                other.m_cnt = nullptr;
            }
            return *this;
        }
        
        //----------------------------------------------------------------------
        // Construct from values
        //----------------------------------------------------------------------
        
        // String
        Config(const char * value) :      m_cnt{new Container{String{value}}} {}
        Config(const String & value) :    m_cnt{new Container{value}} {}
        Config(String && value) noexcept: m_cnt{new Container{std::move(value)}} {}
        
        // Bool
        Config(bool value) : m_cnt{new Container{value}} {}
        
        // Int
        Config(int value) : m_cnt{new Container{value}} {}
        
        // Double
        Config(double value) : m_cnt{new Container{value}} {}

        // Array
        Config(const Array & value) :    m_cnt{new Container{value}} {}
        Config(Array && value) noexcept: m_cnt{new Container{std::move(value)}} {}

        // Map
        Config(const Map & value) :    m_cnt{new Container{value}} {}
        Config(Map && value) noexcept: m_cnt{new Container{std::move(value)}} {}
        
        //----------------------------------------------------------------------
        // Assign values
        //----------------------------------------------------------------------
        
        // String
        
        inline Config & operator = (const char * val)
        {
            m_cnt->m_value = String(val);
            return *this;
        }
        
        inline Config & operator = (const String & val)
        {
            m_cnt->m_value = val;
            return *this;
        }
        
        inline Config & operator = (String && val)
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        // nullptr, bool, int, double
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_VAL_ASSIGN>()>::type>
        inline Config & operator = (T val)
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        // Array
        
        inline Config & operator = (const Array & val)
        {
            m_cnt->m_value = val;
            return *this;
        }
        
        inline Config & operator = (Array && val)
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        // Map
        
        inline Config & operator = (const Map & val)
        {
            m_cnt->m_value = val;
            return *this;
        }
        
        inline Config & operator = (Map && val)
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        //----------------------------------------------------------------------
        // Get values
        //----------------------------------------------------------------------
        
        inline auto GetString() const { return Get<String>(); }
        inline auto GetBool()   const { return Get<bool>(); }
        inline auto GetInt()    const { return Get<int>(); }
        inline auto GetDouble() const { return Get<double>(); }
        inline auto GetArray()  const { return Get<Array>(); }
        inline auto GetMap()    const { return Get<Map>(); }
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_TYPES>()>::type>
        inline const optional<T> Get() const
        {
            auto & v = m_cnt->m_value;
            if (v.type() == typeid(T)) {
                return optional<T>{boost::get<T>(v)};
            }
            return {};
        }
        
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_VAL_TYPES>()>::type>
        inline const optional<std::vector<T>> AsArray() const
        {
            if (!IsArray()) {
                return {};
            }
            auto res = make_optional(std::vector<T>());
            auto & arr = boost::get<Array&>(m_cnt->m_value);
            res->reserve(arr.size());
            for (auto & value : arr) {
                auto & v = value.m_cnt->m_value;
                if (v.type() == typeid(T)) {
                    res->emplace_back(boost::get<T>(v));
                }
            }
            return res;
        }
        
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_VAL_TYPES>()>::type>
        inline const optional<StringMap<T>> AsMap() const
        {
            if (!IsMap()) {
                return {};
            }
            auto res = make_optional(StringMap<T>());
            for (auto & entry : boost::get<Map&>(m_cnt->m_value)) {
                auto & v = entry.second.m_cnt->m_value;
                if (v.type() == typeid(T)) {
                    res->emplace(std::make_pair(entry.first, boost::get<T>(v)));
                }
            }
            return res;
        }
        
        
        //----------------------------------------------------------------------
        // Query value type
        //----------------------------------------------------------------------
        
        
        String GetTypeName() const;
        inline Type GetType()  const { return (Type)m_cnt->m_value.which(); }
        inline bool IsNull()   const { return GetType() == Type::Null; }
        inline bool IsString() const { return GetType() == Type::String; }
        inline bool IsBool()   const { return GetType() == Type::Bool; }
        inline bool IsInt()    const { return GetType() == Type::Int; }
        inline bool IsDouble() const { return GetType() == Type::Double; }
        inline bool IsArray()  const { return GetType() == Type::Array; }
        inline bool IsMap()    const { return GetType() == Type::Map; }
        
    private:
        
        struct Container {
            boost::variant<FBIDE_CONFIG_TYPES> m_value;
            unsigned int m_counter = 1;
        };
        
        Container * m_cnt;
    };
    
    /**
     * Print the type to the stream
     */
    std::ostream& operator << (std::ostream& stream, const Config::Type& type);
}
