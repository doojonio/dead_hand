#pragma once

#include "base/channel.h"
#include "base/message.h"
#include <mailio/message.hpp>

namespace comms {
    class EmailChannel : Channel {
    public:
        void send_message(std::unique_ptr<Message>) override;
    private:
        ChannelType type = ChannelType::EMAIL;
    };

    class EmailMessage : Message {
        MessageType type = MessageType::EMAIL;
    };
} // namespace app
