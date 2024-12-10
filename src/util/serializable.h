#pragma once
#include <string>

namespace util {
    template <typename T>
    struct Serializable {
        [[nodiscard]] virtual std::string ser();
        [[nodiscard]] static T de(const std::string& s) { return T::de_impl(s);};
    };
} // namespace util
