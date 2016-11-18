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
        // Default and nullptr_t. Others let compiler generate automatically
        //----------------------------------------------------------------------
        
        Config(): m_cnt{std::make_shared<Container>(nullptr)} {}
        Config(std::nullptr_t): Config() {}
        
        
        //----------------------------------------------------------------------
        // Construct from values
        //----------------------------------------------------------------------
        
        // String
        Config(const char * value) :      m_cnt{std::make_shared<Container>(String{value})} {}
        Config(const String & value) :    m_cnt{std::make_shared<Container>(value)} {}
        Config(String && value) noexcept: m_cnt{std::make_shared<Container>(std::move(value))} {}
        
        // Bool
        Config(bool value) : m_cnt{std::make_shared<Container>(value)} {}
        
        // Int
        Config(int value) : m_cnt{std::make_shared<Container>(value)} {}
        
        // Double
        Config(double value) : m_cnt{std::make_shared<Container>(value)} {}

        // Array
        Config(const Array & value) :    m_cnt{std::make_shared<Container>(value)} {}
        Config(Array && value) noexcept: m_cnt{std::make_shared<Container>(std::move(value))} {}

        // Map
        Config(const Map & value) :    m_cnt{std::make_shared<Container>(value)} {}
        Config(Map && value) noexcept: m_cnt{std::make_shared<Container>(std::move(value))} {}
        
        
        //----------------------------------------------------------------------
        // Assign values
        //----------------------------------------------------------------------
        
        // String
        
        inline Config & operator = (const char * val) noexcept
        {
            m_cnt->m_value = String(val);
            return *this;
        }
        
        inline Config & operator = (const String & val) noexcept
        {
            m_cnt->m_value = val;
            return *this;
        }
        
        inline Config & operator = (String && val) noexcept
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        // nullptr, bool, int, double
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_VAL_ASSIGN>()>::type>
        inline Config & operator = (T val) noexcept
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        // Array
        
        inline Config & operator = (const Array & val) noexcept
        {
            m_cnt->m_value = val;
            return *this;
        }
        
        inline Config & operator = (Array && val) noexcept
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        
        // Map
        
        inline Config & operator = (const Map & val) noexcept
        {
            m_cnt->m_value = val;
            return *this;
        }
        
        inline Config & operator = (Map && val) noexcept
        {
            m_cnt->m_value = std::move(val);
            return *this;
        }
        

        //----------------------------------------------------------------------
        // Comparison, Config, const char*, values
        //----------------------------------------------------------------------
        
        bool operator == (const Config & rhs) const noexcept;
        
        bool operator != (const Config & rhs) const noexcept
        {
            return !operator==(rhs);
        }
        
        inline bool operator==(const char * rhs) const noexcept
        {
            return operator==(String(rhs));
        }
        inline bool operator!=(const char * rhs) const noexcept
        {
            return operator!=(String(rhs));
        }
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_TYPES>()>::type>
        inline bool operator==(const T& rhs) const noexcept
        {
            auto & v = m_cnt->m_value;
            if (v.type() == typeid(T)) {
                return boost::get<T&>(v) == rhs;
            }
            return false;
        }
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_TYPES>()>::type>
        inline bool operator!=(const T& rhs) const noexcept
        {
            return !operator==(rhs);
        }
        
        
        //----------------------------------------------------------------------
        // Get values
        //----------------------------------------------------------------------
        
        inline auto GetString() const noexcept { return Get<String>(); }
        inline auto GetBool()   const noexcept { return Get<bool>(); }
        inline auto GetInt()    const noexcept { return Get<int>(); }
        inline auto GetDouble() const noexcept { return Get<double>(); }
        inline auto GetArray()  const noexcept { return Get<Array>(); }
        inline auto GetMap()    const noexcept { return Get<Map>(); }
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_TYPES>()>::type>
        inline const optional<T> Get() const noexcept
        {
            auto & v = m_cnt->m_value;
            if (v.type() == typeid(T)) {
                return optional<T>{boost::get<T>(v)};
            }
            return {};
        }
        
        
        template<typename T, typename = typename std::enable_if<is_one_of<T, FBIDE_CONFIG_VAL_TYPES>()>::type>
        inline const optional<std::vector<T>> AsArray() const noexcept
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
        inline const optional<StringMap<T>> AsMap() const noexcept
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
        
        String GetTypeName() const noexcept;
        inline Type GetType()  const noexcept { return (Type)m_cnt->m_value.which(); }
        inline bool IsNull()   const noexcept { return GetType() == Type::Null; }
        inline bool IsString() const noexcept { return GetType() == Type::String; }
        inline bool IsBool()   const noexcept { return GetType() == Type::Bool; }
        inline bool IsInt()    const noexcept { return GetType() == Type::Int; }
        inline bool IsDouble() const noexcept { return GetType() == Type::Double; }
        inline bool IsArray()  const noexcept { return GetType() == Type::Array; }
        inline bool IsMap()    const noexcept { return GetType() == Type::Map; }
        
    private:
        using ValueType = boost::variant<FBIDE_CONFIG_TYPES>;
        struct Container {
            ValueType m_value;
            Container(ValueType && value) : m_value(std::move(value)) {}
        };
        std::shared_ptr<Container> m_cnt;
        
        template<typename T>
        inline T& value() noexcept
        {
            return boost::get<T&>(m_cnt->m_value);
        }
        
        template<typename T>
        inline const T& as() const noexcept
        {
            return boost::get<const T&>(m_cnt->m_value);
        }
    };

    std::ostream& operator << (std::ostream& stream, const Config& type);
    std::ostream& operator << (std::ostream& stream, const Config::Type& type);
}
