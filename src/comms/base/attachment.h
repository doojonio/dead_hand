#pragma once

#include <string>
#include <vector>

#include "util/http.h"
#include "util/url.h"

namespace comms {
    struct Attachment {
        std::string id;
        std::string filename;
        net::MimeType mime_type;
        std::vector<net::Url> urls;
        // app::Crypto crypto;
    };

} // namespace app