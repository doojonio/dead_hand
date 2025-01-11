#pragma once

#include "util/crypto_registry.h"
#include "ids.h"
#include "comms/email.h"
#include "protocols/dmsg.h"

namespace registries {
    extern util::CryptoRegistry<ChannelId, comms::BaseChannel> channels;
    extern util::CryptoRegistry<RecipientGroupId, comms::BaseRecipientGroup> rgroups;
    extern util::CryptoRegistry<AttachmentId, comms::Attachment> attachments;
    extern util::CryptoRegistry<MessageId, comms::BaseMessage> messages;
    extern util::CryptoRegistry<ProtocolId, protocols::BaseProtocol> protocols;
} // namespace registries


