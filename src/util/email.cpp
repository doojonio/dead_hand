#include "util/email.h"
#include "email.h"

namespace util {
    Email::Email(std::string value) : value(value) {
        validate();
    }
    std::string util::Email::get() const {
        return value;
    }


    void util::Email::validate() {
        // TODO: impl
    }

} // namespace email

