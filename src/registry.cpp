#include "registry.h"
#include "comms/email.h"



void Registry::add_email_channel(ChannelId channel_id, std::shared_ptr<comms::EmailChannel> channel) {
    em_channels[channel_id] = channel;
}

std::shared_ptr<comms::EmailChannel> Registry::get_email_channel(ChannelId channel_id) {
    return em_channels[channel_id];
}
