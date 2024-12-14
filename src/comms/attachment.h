#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

#include "util/www/url.h"

using json = nlohmann::json;

namespace comms {
    struct Attachment {
        std::string mime;
        util::www::Url url;
        Attachment(const json& j);
        [[nodiscard]] std::string ser();
        [[nodiscard]] static std::unique_ptr<Attachment> de(const std::string& s);
    };
} // namespace comms
