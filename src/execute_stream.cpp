//
// Created by Nekbakht Zabirov on 18.03.2025.
//

#include "execute_stream.hpp"

namespace nek::sql
{
    ExecuteStream::ExecuteStream(const std::string_view& value) : SqlStream(value)
    {
    }

    ExecuteStream ExecuteStream::insert()
    {
        return ExecuteStream("INSERT");
    }

    ExecuteStream ExecuteStream::update(const std::string_view& table)
    {
        return ExecuteStream("UPDATE " + std::string(table));
    }

    ExecuteStream ExecuteStream::Delete(const std::string_view& table)
    {
        return ExecuteStream("DELETE FROM " + std::string(table));
    }

    ExecuteStream&& ExecuteStream::into(const std::string_view& table, std::initializer_list<std::string_view> columns) &&
    {
        append(" INTO ");
        append(table);

        append(" (");

        for (auto it = columns.begin(); it != columns.end(); ++it)
        {
            append(*it);
            if (std::next(it) != columns.end())
            {
                append(",");
            }
        }

        append(" )");

        return std::move(*this);
    }

    ExecuteStream&& ExecuteStream::set(const std::initializer_list<Column> columns) &&
    {
        os_ << " SET ";

        bool isFirst = true;
        for (const auto & column : columns)
        {
            if (column.str().empty()) {
                continue;
            }

            if (!isFirst)
            {
                os_ << ", ";
            }

            os_ << column.str();

            isFirst = false;
        }

        return std::move(*this);
    }

    ExecuteStream&& ExecuteStream::returning(const std::initializer_list<std::string_view> &columns) &&
    {
        os_ << " RETURNING ";

        for (auto it = columns.begin(); it != columns.end(); ++it)
        {
            os_ << *it;
            if (std::next(it) != columns.end())
            {
                os_ << ", ";
            }
        }

        return std::move(*this);
    }

    ExecuteStream&& ExecuteStream::where(const Conditional& condition) &&
    {
        append(" WHERE ");
        append(condition);
        return std::move(*this);
    }

    ExecuteStream&& ExecuteStream::onConflict(const std::initializer_list<std::string_view> &columns) &&
    {
        os_ << " ON CONFLICT (";

        for (auto it = columns.begin(); it != columns.end(); ++it)
        {
            os_ << *it;
            if (std::next(it) != columns.end())
            {
                os_ << ", ";
            }
        }

        os_ << ")";

        return std::move(*this);
    }

    ExecuteStream&& ExecuteStream::doUpdate() &&
    {
        os_ << " DO UPDATE";

        return std::move(*this);
    }



}