//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#ifndef FORMAT_VALUE_HPP
#define FORMAT_VALUE_HPP

#include <string>
#include <optional>
#include <chrono>
#include <vector>
#include <sstream>

namespace nek::sql
{
    template <typename T>
    constexpr std::string formatValue(const T& value)
    {
        return std::to_string(value);
    }

    inline std::string formatValue(const char* value)
    {
        return std::string("'") + value + "'";
    }

    template <>
    inline std::string formatValue(const char* const& value)
    {
        return std::string("'") + value + "'";
    }

    template <>
    inline std::string formatValue(const std::string& value)
    {
        return "'" + value + "'";
    }

    template <>
    inline std::string formatValue(const std::string_view& value)
    {
        return "'" + std::string(value) + "'";
    }

    template <>
    inline std::string formatValue(const bool& value)
    {
        return value ? "TRUE" : "FALSE";
    }

    template <>
    inline std::string formatValue(const std::chrono::system_clock::time_point& value)
    {
        auto time_t_value = std::chrono::system_clock::to_time_t(value);
        std::tm* tm_value = std::localtime(&time_t_value);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_value);
        return std::string(buffer);
    }

    template <typename T>
    constexpr std::string formatValue(const std::optional<T>& value)
    {
        if (!value)
        {
            return "NULL";
        }

        return formatValue(value.value());
    }

    template <>
    inline std::string formatValue(const std::vector<std::string>& value)
    {
        std::stringstream ss;

        for (const auto & v : value)
        {
            ss << v;
            if (v != value.back())
            {
                ss << ", ";
            }
        }

        return ss.str();
    }
}

#endif //FORMAT_VALUE_HPP
