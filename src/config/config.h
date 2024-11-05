#pragma once

#include <string>
#include <vector>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "util/url.h"

using json = nlohmann::json;

namespace app {
    struct Attachment {
        std::vector<net::Url> urls;
    };

    struct Group;

    class Config {
    public:
        void operator<<(std::string&& content) {
            // json data = json::parse(content);
        };

    private:
        std::vector<Attachment> attachments;
    };

} // namespace Config
