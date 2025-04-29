//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <numeric>
#include <optional>
#include <string>
#include <format>
#include "sql_stream.hpp"
#include "conditional.hpp"
#include <vector>

namespace nek::sql
{
    class Column final : public SqlStream
    {
    public:
        explicit Column(const std::string_view& name);

        Column(const Column& other): SqlStream(other.str())
        {
        }

        static Conditional emptyCondition() {
            return Conditional("");
        }

        static Column empty()
        {
            return Column("");
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Column&& operator=(const T& value)
        {
            append(key);
            append(" = ");
            append(formatValue(value));
            return std::move(*this);
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Column&& operator=(const std::optional<T>& value)
        {
            if (!value)
            {
                return std::move(*this);
            }

            append(key);
            append(" = ");
            append(formatValue(value.value()));
            return std::move(*this);
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator==(const T& value)
        {
            return Conditional(std::format("{} = {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator==(const std::optional<T>& value)
        {
            return Conditional(value ? std::format("{} = {}", key, formatValue(value.value())) : "");
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator!=(const T& value)
        {
            return Conditional(std::format("{} != {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator>(const T& value)
        {
            return Conditional(std::format("{} > {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator>=(const T& value)
        {
            return Conditional(std::format("{} >= {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator<(const T& value)
        {
            return Conditional(std::format("{} < {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional operator<=(const T& value)
        {
            return Conditional(std::format("{} < {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional like(const T& value)
        {
            return Conditional(std::format("{} ILIKE {}", key, formatValue(value)));
        }

        template <typename T, std::enable_if_t<!std::is_same_v<T, Column>, int>  = 0>
        Conditional like(const std::optional<T>& value)
        {
            return Conditional(value ? std::format("{} ILIKE {}", key, formatValue(value.value())) : "");
        }

        template <class T>
        Conditional in(const std::initializer_list<T> values)
        {
            std::ostringstream query;

            int index = 0;
            query << std::accumulate(values.begin(), values.end(), std::string{},
                                     [&index](const std::string& acc, const T& value)
                                     {
                                         return acc + (index++ > 0 ? ", " : "") + formatValue(value);
                                     });

            return Conditional(std::format("{} IN ({})", key, query.str()));
        }

        template <class T>
        Conditional in(const std::vector<T> values)
        {
            std::ostringstream query;

            int index = 0;
            query << std::accumulate(values.begin(), values.end(), std::string{},
                                     [&index](const std::string& acc, const T& value)
                                     {
                                         return acc + (index++ > 0 ? ", " : "") + formatValue(value);
                                     });

            return Conditional(std::format("{} IN ({})", key, query.str()));
        }

        template <class T>
        Conditional any(const std::initializer_list<T> values)
        {
            std::ostringstream query;

            int index = 0;
            query << std::accumulate(values.begin(), values.end(), std::string{},
                                     [&index](const std::string& acc, const T& value)
                                     {
                                         return acc + (index++ > 0 ? ", " : "") + formatValue(value);
                                     });

            return Conditional(std::format("{} IN ({})", key, query.str()));
        }

        Column&& operator=(const Column& value);

        Conditional operator==(const Column& value);

        Conditional operator!=(const Column& value);

        Conditional operator>(const Column& value);

        Conditional operator>=(const Column& value);

        Conditional operator<(const Column& value);

        Conditional operator<=(const Column& value);

    private:
        std::string_view key;
    };
}

#endif //COLUMN_HPP
