#pragma once
#include "ids.h"

#include <memory>
#include "nlohmann/json.hpp"
#include "util/serializable.h"

using json = nlohmann::json;

namespace comms
{
    struct BaseRecipientGroup {
        virtual std::string ser() = 0;
        virtual ~BaseRecipientGroup() {};
    };
    struct BaseMessage {
        ChannelId channel;
        RecipientGroupId rgroup;
        virtual std::string ser() = 0;
        virtual ~BaseMessage() {};
    };
    struct BaseChannel {
        virtual std::string ser() = 0;
        virtual void send(std::unique_ptr<BaseMessage> msg) = 0;
        virtual ~BaseChannel() {};
    };
} // namespace comms
