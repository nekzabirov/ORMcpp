//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#include "sql_stream.hpp"

namespace nek::sql {
    SqlStream::SqlStream(const std::string_view &query) {
        os_ << query;
    }

    SqlStream::~SqlStream() = default;

    SqlStream &&operator<<(SqlStream &&left, const SqlStream &&right) {
        return std::move(left) << right.os_.str();
    }

    std::string SqlStream::build() const {
        return os_.str() + ";";
    }

    SqlStream::SqlStream(SqlStream &&other) noexcept {
        os_ << std::move(other.os_).str();
    }

    SqlStream & SqlStream::operator=(SqlStream &&other) noexcept {
        if (this != &other) {
            os_ << std::move(other.os_).str();
        }
        return *this;
    }

    void SqlStream::append(const std::string_view &str) {
        os_ << str;
    }

    void SqlStream::append(const SqlStream &other) {
        os_ << other.os_.str();
    }

    std::string SqlStream::str() const {
        return os_.str();
    }

    bool SqlStream::empty() const {
        return os_.str().empty();
    }
}
