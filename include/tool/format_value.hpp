//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#ifndef FORMAT_VALUE_HPP
#define FORMAT_VALUE_HPP

#include <string>

namespace nek::sql {
    template<typename T>
    constexpr std::string formatValue(const T &value) {
        return std::to_string(value);
    }

    inline std::string formatValue(const char *value) {
        return std::string("'") + value + "'";
    }

    template<>
    inline std::string formatValue(const char *const&value) {
        return std::string("'") + value + "'";
    }

    template<>
    inline std::string formatValue(const std::string &value) {
        return "'" + value + "'";
    }

    template<>
    inline std::string formatValue(const std::string_view &value) {
        return "'" + std::string(value) + "'";
    }

    template<>
    inline std::string formatValue(const bool &value) {
        return value ? "TRUE" : "FALSE";
    }
}


#endif //FORMAT_VALUE_HPP
