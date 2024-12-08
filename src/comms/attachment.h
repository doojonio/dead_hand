#pragma once

#include <string>
#include "util/www.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace comms
{
    struct Attachment {
        std::string mime;
        util::Url url;
        Attachment(const json& j) :
            mime(j.at("mime").get<std::string>()),
            url(util::Url(j.at("url").get<std::string>())) {
        };
    };
} // namespace comms
