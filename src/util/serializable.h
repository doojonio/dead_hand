#pragma once
#include <string>
#include <memory>

namespace util {
    template <typename T>
    struct Serializable {
        [[nodiscard]] virtual std::string ser();
        [[nodiscard]] static std::unique_ptr<T> de(const std::string& s) { return T::de_impl(s);};
    };
} // namespace util
