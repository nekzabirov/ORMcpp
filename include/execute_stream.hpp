//
// Created by Nekbakht Zabirov on 18.03.2025.
//

#ifndef EXECUTE_STREAM_HPP
#define EXECUTE_STREAM_HPP
#include "column.hpp"
#include "sql_stream.hpp"

namespace nek::sql {
    class ExecuteStream final : public SqlStream {
    public:
        ExecuteStream(const std::string_view &value);

        static ExecuteStream insert();

        static ExecuteStream update(const std::string_view &table);

        static ExecuteStream Delete(const std::string_view &table);

        ExecuteStream &&into(const std::string_view &table, std::initializer_list<std::string_view> columns) &&;

        template<class... T>
        ExecuteStream &&values(const T &... vals) {
            os_ << " VALUES " << "(";

            bool isFirst = true;

            auto nAppend = [&isFirst, this](const std::string &key) {
                if (!isFirst) {
                    os_ << ", ";
                } else {
                    isFirst = false;
                }
                os_ << key;
            };

            (nAppend(formatValue(vals)), ...);

            os_ << ")";

            return std::move(*this);
        }

        ExecuteStream &&set(std::initializer_list<Column> columns) &&;

        ExecuteStream &&returning(const std::initializer_list<std::string_view> &columns) &&;

        ExecuteStream &&where(const Conditional &condition) &&;

        ExecuteStream &&onConflict(const std::initializer_list<std::string_view> &columns) &&;

        ExecuteStream &&doUpdate() &&;

        ExecuteStream &&doNothing() &&;

        ExecuteStream &&doDelete() &&;

        ExecuteStream &&doInsert() &&;

        ExecuteStream &&doReplace() &&;
    };
}

#endif //EXECUTE_STREAM_HPP
