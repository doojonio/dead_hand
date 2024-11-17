#pragma once

namespace cfg {
    struct Channel {
        enum class Type {
            EMAIL
        };
        Channel::Type type;

        virtual ~Channel() {}
    };
} // namespace cfg