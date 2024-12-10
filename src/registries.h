#include "util/crypto_registry.h"
#include "ids.h"
#include "comms/email.h"

namespace registries {
    static util::CryptoRegistry<ChannelId, comms::EmailChannel> email_channels;
    static util::CryptoRegistry<MessageId, comms::EmailMessage> email_messages;
    static util::CryptoRegistry<RecipientGroupId, comms::EmailRecipientGroup> email_rgs;
} // namespace registries


