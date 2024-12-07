#include <string>

namespace util {
    template<typename T>
    class E {
        T value;
    public:
        // TODO: encr
        inline E(T&& v) : value(v) {}
        [[nodiscard]] inline T get() { return value };
    };
} // namespace encr

