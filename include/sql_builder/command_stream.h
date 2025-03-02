//
// Created by Nekbakht Zabirov on 24.10.2024.
//
#ifndef COMMAND_STREAM_H
#define COMMAND_STREAM_H
#include <sstream>
#include <string>
#include "sql_param.hpp"

namespace nek::sql {
    class CommandStream {
    public:
        explicit CommandStream(const std::string_view &command) {
            os_ << command;
        }

        explicit CommandStream(std::ostringstream &os) {
            os_ = std::move(os);
        }

        ~CommandStream() {
        }

    protected:
        CommandStream(const CommandStream &other) {
            os_ << other.os_.str();
        }

        CommandStream(CommandStream &&other) noexcept {
            os_ << std::move(other.os_).str();
        }

        CommandStream &operator=(const CommandStream &other) {
            if (this != &other) {
                os_.str(other.os_.str());
            }
            return *this;
        }

        CommandStream &operator=(CommandStream &&other) noexcept {
            if (this != &other) {
                os_ << std::move(other.os_).str();
            }
            return *this;
        }

        void append(const std::string_view &str) {
            os_ << str;
        }

        void append(const CommandStream &other) {
            os_ << other.os_.str();
        }

    public:
        template<typename T>
        friend CommandStream &&operator<<(CommandStream &&left, const T &right) {
            left.os_ << " " << formatValue(right);
            return std::move(left);
        }

        friend CommandStream &&operator<<(CommandStream &&left, const CommandStream &&right) {
            return std::move(left) << right.os_.str();
        }

        [[nodiscard]] std::string build() const {
            return os_.str() + ";";
        }

        bool empty() const {
            return os_.str().empty();
        }

    private:
        void printMessage(const std::string &message) const {
            std::printf("%s of %p\n", message.c_str(), this);
        }

    protected:
        std::ostringstream os_;
    };
}

#endif // COMMAND_STREAM_H
