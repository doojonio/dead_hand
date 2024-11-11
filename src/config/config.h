#pragma once

#include <string>
#include <vector>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "util/www.h"

using json = nlohmann::json;

namespace cfg {
    struct Attachment {
        std::vector<www::Url> urls;
    };

    struct Group;

    class Config {
    public:
        static void setup_config_from_url(Config& config, www::Url url);

        void operator<<(www::Url content);

    private:
        std::vector<Attachment> attachments;
    };

} // namespace Config
