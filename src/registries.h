#include "util/crypto_registry.h"
#include "ids.h"
#include "comms/email.h"

namespace registries {
    static util::CryptoRegistry<ChannelId, comms::BaseChannel> channels;
    static util::CryptoRegistry<RecipientGroupId, comms::BaseRecipientGroup> rgroups;
    static util::CryptoRegistry<AttachmentId, comms::Attachment> attachments;
    static util::CryptoRegistry<MessageId, comms::BaseMessage> messages;
} // namespace registries


