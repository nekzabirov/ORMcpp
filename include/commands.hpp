//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "column.hpp"

namespace nek::sql {
    static Column column(const std::string_view &key) {
        return Column(key);
    }
}

#endif //COMMANDS_HPP
