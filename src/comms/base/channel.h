#pragma once

#include "message.h"
#include <memory>

namespace comms {

    enum class ChannelType {
        EMAIL,
    };

    class Channel {
    public:
        virtual void send_message(Message&);

    protected:
        ChannelType type;
    };

} // namespace app
