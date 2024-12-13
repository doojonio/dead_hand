#pragma once
#include <unordered_set>
#include <string>

#include <format>
#include <assert.h>

namespace util {
    template <typename TId>
    class GlobalId {
        std::string value;

    protected:
        static std::unordered_set<std::string> registered_ids;

    public:
        inline GlobalId() : value("") {};

        inline GlobalId(std::string id) : value(id) {
            if (id == "" || registered_ids.find(id) == registered_ids.end()) {
                throw std::invalid_argument(std::format("id {} is empty or not registered", id));
            }
        };

        inline static TId register_id(std::string id) {
            if (id == "" || registered_ids.find(id) != registered_ids.end()) {
                throw std::invalid_argument(std::format("id {} is empty or already registered", id));
            }

            registered_ids.insert(id);

            return TId(id);
        };

        [[nodiscard]] inline std::string get() const {
            assert(value != ""); return value;
        }

        inline bool operator==(const GlobalId& other) const {
            return value == other.get();
        }
    };
    template <typename TId>
    std::unordered_set<std::string> GlobalId<TId>::registered_ids;

    template <typename T>
    struct GlobalIdHash {
        inline size_t operator()(const T& obj) const {
            return std::hash<std::string>{}(obj.get());
        }
    };
}
