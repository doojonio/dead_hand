#pragma once

#include <memory>

namespace util {
    template<typename TDerived, typename TBase>
    std::shared_ptr<TDerived> cast_u(std::unique_ptr<TBase> base) {
        return std::dynamic_pointer_cast<TDerived>(std::shared_ptr(std::move(base)));
    }
}
