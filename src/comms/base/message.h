#pragma once

#include <string>
#include <vector>

namespace comms {
    enum class MessageType {
        EMAIL
    };

    class Message {
    protected:
        MessageType type;
        std::string channel;
        std::string recipient_group;
        std::vector<std::string> attachments;
    };
} // namespace comms
