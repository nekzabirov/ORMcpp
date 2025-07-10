//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#ifndef SQL_STREAM_HPP
#define SQL_STREAM_HPP
#include <sstream>
#include "format_value.hpp"

namespace nek::sql {
    class SqlStream {
    public:
        explicit SqlStream(const std::string_view &query);

        ~SqlStream();

        SqlStream(SqlStream &&other) noexcept;

        SqlStream &operator=(SqlStream &&other) noexcept;

        template<typename T>
        friend SqlStream &&operator<<(SqlStream &&left, const T &right) {
            left.os_ << " " << formatValue(right);
            return std::move(left);
        }

        friend SqlStream &&operator<<(SqlStream &&left, const SqlStream &&right);

        std::string str() const;

        std::string build() const;

        std::ostringstream os_;

        void append(const std::string_view &str);

        void append(const SqlStream &other);

        bool empty() const;
    };
}

#endif //SQL_STREAM_HPP
