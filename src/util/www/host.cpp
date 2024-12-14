#include <format>

#include "host.h"

namespace util::www {

    Host::Host(std::string value) : value(value) {
        std::regex re("^[^\\d.][\\w.]+"); // I don't care
        if (!std::regex_match(value, re)) {
            throw std::invalid_argument(std::format("invalid host: {}", value));
        }
    };

    [[nodiscard]] std::string Host::get() const {
        return value;
    };
} // namespace util::wwww
