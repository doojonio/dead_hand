#include <string>

namespace util {
    template<typename T>
    class Crypted {
        std::string value;

        std::string encrypt__(const std::string& str, char key) {
            std::string encrypted;
            for (char c : str) {
                encrypted += c ^ key;
            }
            return encrypted;
        }

        std::string decrypt__(const std::string& str, char key) {
            return encrypt__(str, key);
        }

    public:
        // TODO: encr
        inline Crypted(T&& v) : value(encrypt__(v.ser(), 'a')) { };
        [[nodiscard]] inline T decrypt() { return T::de(decrypt__(value, 'a')); };
    };
} // namespace encr

