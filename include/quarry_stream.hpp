//
// Created by Nekbakht Zabirov on 18.03.2025.
//

#ifndef QUARRY_STREAM_HPP
#define QUARRY_STREAM_HPP

#include "sql_stream.hpp"
#include "conditional.hpp"

namespace nek::sql
{
    class QuarryStream final : public SqlStream
    {
    public:
        explicit QuarryStream(const std::string_view& value);

        static QuarryStream select(const std::initializer_list<std::string_view>& keys);

        QuarryStream&& from(const std::string_view& table) &&;

        QuarryStream&& from(const std::string_view& table, const std::string_view& as) &&;

        QuarryStream&& where(const Conditional& condition) &&;

        QuarryStream&& orderBy(const std::string_view& column, const std::string_view& order) &&;

        QuarryStream&& limit(const int& limit) &&;

        QuarryStream&& offset(const int& offset) &&;

        QuarryStream&& groupBy(const std::string_view& column) &&;

        QuarryStream&& leftJoin(const std::string_view& table, const std::string_view& as, const Conditional&& on) &&;

        QuarryStream&& rightJoin(const std::string_view& table, const std::string_view& as, const Conditional&& on) &&;

        QuarryStream&& innerJoin(const std::string_view& table, const std::string_view& as, const Conditional&& on) &&;
    };
}

#endif //QUARRY_STREAM_HPP
