//
// Created by Nekbakht Zabirov on 25.10.2024.
//

#ifndef QUARRY_COMMAND_STREAM_HP
#define QUARRY_COMMAND_STREAM_HP

#include "command_stream.h"
#include "parrams.hpp"
#include "conditional_stream.hpp"

namespace nek::sql {
    class QuarryCommandStream : public CommandStream {
    public:
        template<Streamable... Key>
        static QuarryCommandStream Select(const Key &... keys) {
            std::ostringstream query;
            query << "SELECT ";

            bool isFirst = true;

            auto append = [&query, &isFirst](const std::string &key) {
                if (!isFirst) {
                    query << ", ";
                } else {
                    isFirst = false;
                }
                query << key;
            };

            (append(std::string(keys)), ...);

            return QuarryCommandStream(query);
        }

        static QuarryCommandStream Select() {
            return QuarryCommandStream("SELECT *");
        }

        QuarryCommandStream &&from(const std::string_view &table_name) && {
            os_ << " FROM " << table_name;

            return std::move(*this);
        }

        QuarryCommandStream &&from(const std::string_view &table_name, const std::string_view &as) && {
            os_ << " FROM " << table_name << " " << as;

            return std::move(*this);
        }

        QuarryCommandStream &&where(const ConditionalStream &&conditional_stream) && {
            if (conditional_stream.empty()) {
                return std::move(*this);
            }

            append(" Where ");
            append(conditional_stream);

            return std::move(*this);
        }

        QuarryCommandStream &&limit(const int &limit) && {
            append(" LIMIT ");
            append(formatValue(limit));

            return std::move(*this);
        }

        QuarryCommandStream &&offset(const int &offset) && {
            append(" OFFSET ");
            append(formatValue(offset));

            return std::move(*this);
        }

        QuarryCommandStream &&orderBy(const std::string_view &column, const std::string_view &order) && {
            append(" ORDER BY ");
            append(column);
            append(" ");
            append(order);

            return std::move(*this);
        }

        QuarryCommandStream &&leftJoin(const std::string_view &table_name,
                                       const std::string_view &as,
                                       const ConditionalStream &&on) && {
            os_ << " LEFT JOIN " << table_name << " " << as;
            append(" ON ");
            append(on);

            return std::move(*this);
        }

    private:
        explicit QuarryCommandStream(const std::string_view &command) : CommandStream(command) {
        }

        explicit QuarryCommandStream(std::ostringstream &os) : CommandStream(os) {
        }
    };
}

#endif //QUARRY_COMMAND_STREAM_HP
