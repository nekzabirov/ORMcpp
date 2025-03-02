//
// Created by Nekbakht Zabirov on 02.03.2025.
//

#ifndef EXECUT_COMMAND_STREAM_HPP
#define EXECUT_COMMAND_STREAM_HPP

#include "command_stream.h"
#include "parrams.hpp"
#include "column.hpp"
#include <algorithm>

namespace nek::sql {
class ExecutCommandStream final : public CommandStream {
public:
  explicit ExecutCommandStream() : CommandStream("") {}

  static ExecutCommandStream insert(const std::string_view &table,
                               const std::initializer_list<std::string_view> &columns) {
    ExecutCommandStream stream;

    stream.os_ << "INSERT INTO " << table;

    stream.os_ << " (";

    for (auto it = columns.begin(); it != columns.end(); ++it) {
      stream.os_ << *it;
      if (std::next(it) != columns.end()) {
        stream.os_ << ", ";
      }
    }

    stream.os_ << ")";

    return stream;
  }

  template<class... T>
  ExecutCommandStream &&values(const T &... vals) {
    os_ << " VALUES " << "(";

    bool isFirst = true;

    auto nAppend = [&isFirst, this](const std::string &key) {
      if (!isFirst) {
        os_ << ", ";
      } else {
          isFirst = false;
      }
      os_ << key;
    };

    (nAppend(formatValue(vals)), ...);

    os_ << ")";

    return std::move(*this);
  }

  ExecutCommandStream &&returning(const std::initializer_list<std::string_view> &columns) {
    os_ << " RETURNING ";

    for (auto it = columns.begin(); it != columns.end(); ++it) {
      os_ << *it;
      if (std::next(it) != columns.end()) {
        os_ << ", ";
      }
    }

    return std::move(*this);
  }

  ExecutCommandStream &&onConflict(const std::initializer_list<std::string_view> &columns) {
    os_ << " ON CONFLICT (";

    for (auto it = columns.begin(); it != columns.end(); ++it) {
      os_ << *it;
      if (std::next(it) != columns.end()) {
        os_ << ", ";
      }
    }

    os_ << ")";

    return std::move(*this);
  }

  ExecutCommandStream &&doUpdate() {
    os_ << " DO UPDATE";

    return std::move(*this);
  }

  ExecutCommandStream &&set(const std::initializer_list<Column> &columns) {
    os_ << " SET ";

    for (auto it = columns.begin(); it != columns.end(); ++it) {
      os_ << it->str();
      if (std::next(it) != columns.end()) {
        os_ << ", ";
      }
    }

    return std::move(*this);
  }
};
}

#endif //EXECUT_COMMAND_STREAM_HPP
