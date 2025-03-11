//
// Created by Nekbakht Zabirov on 15.10.2024.
//

#ifndef SQL_PARAM_HPP
#define SQL_PARAM_HPP

#include <string>
#include "column.hpp"

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
    inline std::string formatValue(const bool &value) {
        return value ? "TRUE" : "FALSE";
    }

    template<>
    inline std::string formatValue(const Column &value) {
        return value.str();
    }
}

#endif //SQL_PARAM_HPP
