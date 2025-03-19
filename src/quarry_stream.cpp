//
// Created by Nekbakht Zabirov on 18.03.2025.
//

#include "quarry_stream.hpp"
#include <sstream>

namespace nek::sql {
    QuarryStream::QuarryStream(const std::string_view &value): SqlStream(value) {
    }

    QuarryStream QuarryStream::select(const std::initializer_list<std::string_view> &keys) {
        std::stringstream ss;

        ss << "SELECT ";

        for (auto it = keys.begin(); it != keys.end(); ++it) {
            ss << *it;
            if (std::next(it) != keys.end()) {
                ss << ", "; // Add separator if not the last key
            }
        }

        return QuarryStream(ss.str());
    }

    QuarryStream &&QuarryStream::from(const std::string_view &table) && {
        append(" FROM ");
        append(table);
        return std::move(*this);
    }

    QuarryStream&& QuarryStream::from(const std::string_view& table, const std::string_view& as) &&
    {
        append(" FROM ");
        append(table);
        append(" AS ");
        append(as);
        return std::move(*this);
    }


    QuarryStream &&QuarryStream::where(const Conditional &condition) && {
        append(" WHERE ");
        append(condition);
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::orderBy(const std::string_view &column, const std::string_view &order) && {
        append(" ORDER BY ");
        append(column);
        append(" ");
        append(order);
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::limit(const int &limit) && {
        append(" LIMIT ");
        append(std::to_string(limit));
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::offset(const int &offset) && {
        append(" OFFSET ");
        append(std::to_string(offset));
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::groupBy(const std::string_view &column) && {
        append(" GROUP BY ");
        append(column);
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::leftJoin(const std::string_view &table, const std::string_view &as, const Conditional &&on) && {
        append(" LEFT JOIN ");
        append(table);
        append(" AS ");
        append(as);
        append(" ON ");
        append(on);
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::rightJoin(const std::string_view &table, const std::string_view &as, const Conditional &&on) && {
        append(" RIGHT JOIN ");
        append(table);
        append(" AS ");
        append(as);
        append(" ON ");
        append(on);
        return std::move(*this);
    }

    QuarryStream &&QuarryStream::innerJoin(const std::string_view &table, const std::string_view &as, const Conditional &&on) && {
        append(" INNER JOIN ");
        append(table);
        append(" AS ");
        append(as);
        append(" ON ");
        append(on);
        return std::move(*this);
    }
}
