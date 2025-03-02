//
// Created by Nekbakht Zabirov on 30.10.2024.
//

#ifndef SQL_HPP
#define SQL_HPP

#include "column.hpp"
#include "execut_command_stream.hpp"
#include "quarry_command_stream.hpp"

namespace nek::sql {
    template<class ... Key>
    static QuarryCommandStream select(const Key &... keys) {
        return QuarryCommandStream::Select(keys...);
    }

    static ExecutCommandStream insert(const std::string_view &table,
                               const std::initializer_list<std::string_view> &columns) {
        return ExecutCommandStream::insert(table, columns);
    }

    static ConditionalStream conditional(const std::string_view &key) {
        return ConditionalStream(key);
    }

    static Column column(const std::string_view &key) {
        return Column(key);
    }

    static Column setExcluded(const std::string_view &key) {
        return Column(key) = Column(std::string("excluded.") + std::string(key));
    }
}

#endif //SQL_HPP
