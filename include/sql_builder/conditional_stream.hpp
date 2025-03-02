//
// Created by Nekbakht Zabirov on 15.10.2024.
//

#ifndef SQL_CONDITIONAL_HPP
#define SQL_CONDITIONAL_HPP

#include "command_stream.h"
#include "sql_param.hpp"

namespace nek::sql {
    class ConditionalStream final : public CommandStream {
    public:
        explicit ConditionalStream(const std::string_view &key): CommandStream(key) {
        };

        template<class T>
        ConditionalStream &&addConditional(const std::string_view &conditional, const T &value) {
            os_ << " " << conditional << " " << formatValue(value);

            return std::move(*this);
        }

        template<class T>
        friend ConditionalStream &&operator==(ConditionalStream &&left, const T &value) {
            return left.addConditional("=", value);
        }

        template<class T>
        friend ConditionalStream &&operator!=(ConditionalStream &&left, const T &value) {
            return left.addConditional("!=", value);
        }

        template<class T>
        friend ConditionalStream &&operator>(ConditionalStream &&left, const T &value) {
            return left.addConditional(">", value);
        }

        template<class T>
        friend ConditionalStream &&operator>=(ConditionalStream &&left, const T &value) {
            return left.addConditional(">=", value);
        }

        template<class T>
        friend ConditionalStream &&operator<(ConditionalStream &&left, const T &value) {
            return left.addConditional("<", value);
        }

        template<class T>
        friend ConditionalStream &&operator<=(ConditionalStream &&left, const T &value) {
            return left.addConditional("<=", value);
        }

        template<class T>
        ConditionalStream &&like(const T &value) {
            return addConditional("LIKE", value);
        }

        friend ConditionalStream &&operator&&(ConditionalStream &&left, ConditionalStream &&right) {
            std::ostringstream os;

            if (left.empty()) {
                os << right.os_.str();
            } else {
                os << "(" << left.os_.str() << " AND " << right.os_.str() << ")";
            }

            left.os_ = std::move(os);

            return std::move(left);
        }

        friend ConditionalStream &&operator||(ConditionalStream &&left, ConditionalStream &&right) {
            std::ostringstream os;

            if (left.empty()) {
                os << right.os_.str();
            } else {
                os << "(" << left.os_.str() << " OR " << right.os_.str() << ")";
            }

            left.os_ = std::move(os);

            return std::move(left);
        }
    };
}

#endif //SQL_CONDITIONAL_HPP
