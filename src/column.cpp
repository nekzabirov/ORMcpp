//
// Created by Nekbakht Zabirov on 12.03.2025.
//

#include "column.hpp"
#include "format_value.hpp"

namespace nek::sql {
    Column::Column(const std::string_view &name) : SqlStream(""), key(name) {
    }

    Column &&Column::operator=(const Column &value) {
        append(key);
        append(" = ");
        append(value.key);
        return std::move(*this);
    }

    Conditional Column::operator==(const Column &value) {
        return Conditional(std::format("{} = {}", key, value.key));
    }

    Conditional Column::operator!=(const Column &value) {
        return Conditional(std::format("{} != {}", key, value.key));
    }

    Conditional Column::operator>(const Column &value) {
        return Conditional(std::format("{} > {}", key, value.key));
    }

    Conditional Column::operator>=(const Column &value) {
        return Conditional(std::format("{} >= {}", key, value.key));
    }

    Conditional Column::operator<(const Column &value) {
        return Conditional(std::format("{} < {}", key, value.key));
    }

    Conditional Column::operator<=(const Column &value) {
        return Conditional(std::format("{} <= {}", key, value.key));
    }
}
