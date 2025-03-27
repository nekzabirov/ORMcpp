//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "column.hpp"
#include "quarry_stream.hpp"
#include "execute_stream.hpp"

namespace nek::sql {
    static Column column(const std::string_view &key) {
        return Column(key);
    }

    static QuarryStream select(const std::initializer_list<std::string_view> &keys) {
      return QuarryStream::select(keys);
    }

    static ExecuteStream insert() {
      return ExecuteStream::insert();
    }

    static ExecuteStream update(const std::string_view &table) {
      return ExecuteStream::update(table);
    }

    static ExecuteStream deleteFrom(const std::string_view &table) {
        return ExecuteStream::Delete(table);
    }
}

#endif //COMMANDS_HPP
