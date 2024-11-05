#pragma once

#include "message.h"
#include <memory>

namespace comms {

    enum class ChannelType {
        EMAIL,
    };

    class Channel {
    public:
        virtual void send_message(std::unique_ptr<Message> message);

    protected:
        ChannelType type;
    };

} // namespace app
