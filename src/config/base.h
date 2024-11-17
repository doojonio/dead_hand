#pragma once

namespace cfg {
    struct Channel {
        enum class Type {
            EMAIL
        };
        Channel::Type type;
    };
} // namespace cfg