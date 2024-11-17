#pragma once

#include <string>
#include <vector>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <config/base.h>
#include "util/www.h"

using json = nlohmann::json;

namespace cfg {
    class Config {
    public:
        void operator<<(www::Url content);

    private:
        std::vector<std::shared_ptr<Channel>> channels;

        void add_attachments(json j_attachments);
        void add_channels(json j_channels);
        void add_recipients_groups(json j_rgroups);
        void add_messages(json j_msgs);
    };

} // namespace Config
