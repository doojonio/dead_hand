#pragma once

namespace comms {
    enum class MessageType {
        EMAIL
    };

    class Message {
    protected:
        MessageType type;
    };
} // namespace app
