#include <unordered_map>
#include <memory>
#include "ids.h"
#include "util/global_id.h"
#include "comms/email.h"

class Registry {
    std::unordered_map<ChannelId, std::shared_ptr<comms::EmailChannel>, util::GlobalIdHash<ChannelId>> em_channels;
public:
    void add_email_channel(ChannelId, std::shared_ptr<comms::EmailChannel>);
    std::shared_ptr<comms::EmailChannel> get_email_channel(ChannelId);
};

