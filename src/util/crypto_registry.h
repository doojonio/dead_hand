#include <unordered_map>
#include <memory>
#include "util/global_id.h"
#include "util/crypto.h"

namespace util {
    template<typename TId, typename T>
    class CryptoRegistry {
        // using DeFunc = std::unqiue_ptr<T>(*)(const std::string&);

        std::unordered_map<TId, std::unique_ptr<Crypted<T>>, util::GlobalIdHash<TId>> objects;
    public:
        template<typename ...Args>
        void add(const std::string& id, std::unique_ptr<T> obj, Crypted<T>::DeFunc de) {
            objects[TId::register_id(id)] = std::make_unique<Crypted<T>>(std::move(obj), de);
        }

        std::unique_ptr<T> get(const TId& id) {
            return objects[id]->decrypt();
        }
    };

} // namespace util

