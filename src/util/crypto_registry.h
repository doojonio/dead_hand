#include <unordered_map>
#include <memory>
#include "util/global_id.h"
#include "util/crypto.h"
#include "util/pointers.h"

namespace util {
    template<typename TId, typename T>
    class CryptoRegistry {
        std::unordered_map<TId, std::unique_ptr<Crypted<T>>, util::GlobalIdHash<TId>> objects;
    public:
        template<typename InType, typename ...Args>
        void add(const std::string& id, Args ...args) {
            objects[TId::register_id(id)] = std::make_unique<Crypted<T>>(
                std::make_unique<InType>(std::forward<Args>(args)...),
                &InType::template de<T>
            );
        }

        std::unique_ptr<T> get(const TId& id) {
            return objects.at(id)->decrypt();
        }

        template<typename InType>
        std::shared_ptr<InType> get(const TId& id) {
            return util::cast_u<InType>(objects.at(id)->decrypt());
        }
    };

} // namespace util

