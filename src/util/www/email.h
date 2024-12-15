#pragma once

#include <string>
#include <mailio/mailboxes.hpp>


namespace util::www {
    class Email {
    public:
        Email(std::string value);
        [[nodiscard]] std::string get() const;

        operator mailio::mail_address() const;

    private:
        std::string value;
        void validate();
    };
} // namespace email
