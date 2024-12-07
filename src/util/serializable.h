
namespace util {
    template <typename T>
    struct BaseSerializable {
        [[nodiscard]] virtual std::string ser;
        [[nodiscard]] virtual T de;
    };
} // namespace util
