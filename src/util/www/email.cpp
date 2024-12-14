#include "email.h"

namespace util::www {
    Email::Email(std::string value) : value(value) {
        validate();
    }
    std::string Email::get() const {
        return value;
    }


    void Email::validate() {
        // TODO: impl
    }

} // namespace email

