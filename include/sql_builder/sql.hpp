//
// Created by Nekbakht Zabirov on 30.10.2024.
//

#ifndef SQL_HPP
#define SQL_HPP

#include "quarry_command_stream.hpp"

namespace nek::sql {
    template<class ... Key>
    static QuarryCommandStream select(const Key &... keys) {
        return QuarryCommandStream::Select(keys...);
    }

    static ConditionalStream column(const std::string_view &key) {
        return ConditionalStream(key);
    }
}

#endif //SQL_HPP
