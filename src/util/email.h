#pragma once

#include <string>


namespace util {
    class Email {
    public:
        Email(std::string value);
        [[nodiscard]] std::string get() const;

    private:
        std::string value;
        void validate();
    };
} // namespace email
