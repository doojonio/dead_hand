#pragma once

#include <string>


namespace util {
    class Email {
    public:
        inline Email(std::string value) : value(value) {
            validate();
        }

        [[nodiscard]] std::string get() const;

    private:
        std::string value;

        void validate();
    };
} // namespace email
