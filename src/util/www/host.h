#pragma once
#include <stdexcept>
#include <regex>
#include <string>

namespace util::www {

    class Host {
    public:
        Host(std::string value);
        [[nodiscard]] std::string get() const;
    private:
        std::string value;
    };

} // namespace www::util
