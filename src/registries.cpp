#include "registries.h"

namespace registries {
    util::CryptoRegistry<ChannelId, comms::BaseChannel> channels;
    util::CryptoRegistry<RecipientGroupId, comms::BaseRecipientGroup> rgroups;
    util::CryptoRegistry<AttachmentId, comms::Attachment> attachments;
    util::CryptoRegistry<MessageId, comms::BaseMessage> messages;
} // namespace registries
