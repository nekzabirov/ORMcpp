//
// Created by Nekbakht Zabirov on 14.03.2025.
//

#ifndef CONDITIONAL_HPP
#define CONDITIONAL_HPP

#include "sql_stream.hpp"

namespace nek::sql
{
    class Conditional : public SqlStream
    {
    public:
        explicit Conditional(const std::string_view& value);

        Conditional&& operator&&(const Conditional&& right)
        {
            if (empty())
            {
                return std::move(*this);
            }

            std::ostringstream os;

            os << "(" << os_.str() << " AND " << right.os_.str() << ")";

            os_ = std::move(os);

            return std::move(*this);
        }

        Conditional&& operator||(const Conditional&& right)
        {
            if (empty())
            {
                return std::move(*this);
            }

            std::ostringstream os;

            os << "(" << os_.str() << " OR " << right.os_.str() << ")";

            os_ = std::move(os);

            return std::move(*this);
        }
    };
}

#endif //CONDITIONAL_HPP
