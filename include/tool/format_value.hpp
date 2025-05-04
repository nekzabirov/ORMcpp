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
    	std::stringstream result;

    	result << "'";
    	for (const char& c : value)
    	{
    		if (c == '\'')
    		{
    			result << "`";
    		} else
    		{
    			result << c;
    		}
    	}
    	result << "'";

        return result.str();
    }

    template <>
    inline std::string formatValue(const std::string_view& value)
    {
    	std::stringstream result;

    	result << "'";
    	for (const char& c : value)
    	{
    		if (c == '\'')
    		{
    			result << "`";
    		} else
    		{
    			result << c;
    		}
    	}
    	result << "'";

    	return result.str();
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
    	std::string array_str = "{";
    	for (size_t i = 0; i < value.size(); ++i) {
    		if (i > 0) array_str += ",";
    		// Escape quotes in language names if they exist
    		std::string escaped_lang = value[i];
    		size_t pos = 0;
    		while ((pos = escaped_lang.find('\"', pos)) != std::string::npos) {
    			escaped_lang.insert(pos, "\\");
    			pos += 2;
    		}
    		array_str += "\"" + escaped_lang + "\"";
    	}
    	array_str += "}";
    	return array_str;
    }
}

#endif //FORMAT_VALUE_HPP
