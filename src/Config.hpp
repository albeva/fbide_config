//
//  Config.hpp
//  cpp-test
//
//  Created by Albert on 28/10/2016.
//  Copyright © 2016 albeva. All rights reserved.
//
#pragma once
#include "Utils.hpp"

#define VARIANT_TYPE_LIST std::nullptr_t, String, bool, int, double, Array, Map

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
        
        inline const boost::optional<String&> GetString() { return Get<String>(); }
        inline const boost::optional<const String&> GetString() const { return Get<String>(); }
        
        inline const boost::optional<bool &> GetBool() { return Get<bool>(); }
        inline const boost::optional<const bool &> GetBool() const { return Get<bool>(); }
        
        inline const boost::optional<int &> GetInt() { return Get<int>(); }
        inline const boost::optional<const int &> GetInt() const { return Get<int>(); }
        
        inline const boost::optional<double &> GetDouble() { return Get<double>(); }
        inline const boost::optional<const double &> GetDouble() const { return Get<double>(); }
        
        inline const boost::optional<Array &> GetArray() { return Get<Array>(); }
        inline const boost::optional<const Array &> GetArray() const { return Get<Array>(); }
        
        inline const boost::optional<Map &> GetMap() { return Get<Map>(); }
        inline const boost::optional<const Map &> GetMap() const { return Get<Map>(); }
        
        
        template<typename T, typename = std::enable_if<is_one_of<T, VARIANT_TYPE_LIST>()>>
        inline const boost::optional<T&> Get()
        {
            if (GetType() == GetTypeOf<T>()) {
                return {boost::get<T&>(*m_val)};
            }
            return {};
        }
        
        
        template<typename T, typename = std::enable_if<is_one_of<T, VARIANT_TYPE_LIST>()>>
        inline const boost::optional<const T&> Get() const
        {
            if (GetType() == GetTypeOf<T>()) {
                return {boost::get<T&>(*m_val)};
            }
            return {};
        }
        
        
        //----------------------------------------------------------------------
        // Query value type
        //----------------------------------------------------------------------
        
        /**
         * Get Type constant for the given type
         */
        template<typename T, typename = std::enable_if<is_one_of<T, VARIANT_TYPE_LIST>()>>
        static constexpr Type GetTypeOf()
        {
            if (std::is_same<T, std::nullptr_t>()) {
                return Type::Null;
            } else if (std::is_same<T, String>()) {
                return Type::String;
            } else if (std::is_same<T, bool>()) {
                return Type::Bool;
            } else if (std::is_same<T, int>()) {
                return Type::Int;
            } else if (std::is_same<T, double>()) {
                return Type::Double;
            } else if (std::is_same<T, Array>()) {
                return Type::Array;
            } else if (std::is_same<T, Map>()) {
                return Type::Map;
            }
        }
        
        
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
        
        using Storage   = boost::variant<VARIANT_TYPE_LIST>;
        using Container = std::shared_ptr<Storage>;
        
        Container m_val;
    };
    
    /**
     * Print the type to the stream
     */
    std::ostream& operator << (std::ostream& stream, const Config::Type& type);
}
