#pragma once

#include <string>
#include <unordered_set>
#include "util/global_id.h"

class ChannelId : public util::GlobalId<ChannelId> {
        static std::unordered_set<std::string> registered_ids;
};
class RecipientGroupId : public util::GlobalId<ChannelId> {
        static std::unordered_set<std::string> registered_ids;
};
class MessageId : public util::GlobalId<ChannelId> {
        static std::unordered_set<std::string> registered_ids;
};
class ProtocolId : public util::GlobalId<ChannelId> {
        static std::unordered_set<std::string> registered_ids;
};
