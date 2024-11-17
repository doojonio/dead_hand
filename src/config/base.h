#pragma once

#include <string>
#include <vector>

namespace cfg {
    struct Channel {
        enum class Type {
            EMAIL
        };
        Channel::Type type;

        virtual ~Channel() {}
    };

    struct RecipientGroup {
        enum class Type {
            EMAIL
        };
        RecipientGroup::Type type;

        virtual ~RecipientGroup() {}
    };

    struct Message {
        enum class Type {
            EMAIL
        };
        Message::Type type;
        std::string channel;
        std::string recipient_group;
        std::vector<std::string> attachments;

        virtual ~Message() {}

    };
} // namespace cfg