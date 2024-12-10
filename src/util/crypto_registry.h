#include <unordered_map>
#include <memory>
#include "util/global_id.h"
#include "util/crypto.h"

namespace util {
    template<typename TId, typename T>
    class CryptoRegistry {
        std::unordered_map<TId, std::unique_ptr<Crypted<T>>, util::GlobalIdHash<TId>> objects;
    public:
        template<typename ...Args>
        void add(const std::string& id, Args&&... args) {
            objects[TId::register_id(id)] = std::make_unique<Crypted<T>>(T(std::forward<Args>(args)...));
        }

        T get(const TId& id) {
            return objects[id]->decrypt();
        }
    };

} // namespace util

