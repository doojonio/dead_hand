#pragma once

#include <string>


namespace email {
    class Email {
    public:
        Email(std::string value) : value(value) {
            validate();
        }

        std::string get();

    private:
        std::string value;

        void validate();
    };
} // namespace email
