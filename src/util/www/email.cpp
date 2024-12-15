#include "email.h"

namespace util::www {
    Email::Email(std::string value) : value(value) {
        validate();
    }
    std::string Email::get() const {
        return value;
    }

    Email::operator mailio::mail_address() const {
        return mailio::mail_address("", value);
    }


    void Email::validate() {
        // TODO: impl
    }

} // namespace email

