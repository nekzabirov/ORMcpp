//
// Created by Nekbakht Zabirov on 02.03.2025.
//

#ifndef COLUMN_HPP
#define COLUMN_HPP
#include "command_stream.h"

namespace nek::sql {
    class Column final : public CommandStream {
    public:
        explicit Column(const std::string_view &key): CommandStream(key), key(key) {
        };

        template<class T>
        Column &&addConditional(const std::string_view &conditional, const T &value) {
            os_ << " " << conditional << " " << formatValue(value);

            return std::move(*this);
        }

        Column &&addConditional(const std::string_view &conditional, const Column &value) {
            os_ << " " << conditional << " " << value.key;

            return std::move(*this);
        }

        template <class T>
        Column&& operator=(const T&& value) {
            return addConditional("=", value);
        }

        template <class T>
        Column&& operator=(const T& value) {
            return addConditional("=", value);
        }
    private:
        const std::string_view key;
    };
}

#endif //COLUMN_HPP
