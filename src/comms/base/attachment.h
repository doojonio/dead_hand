#pragma once

#include <string>
#include <vector>

#include "util/http.h"
#include "util/www.h"

namespace comms {
    struct Attachment {
        std::string id;
        std::string filename;
        www::MimeType mime_type;
        std::vector<www::Url> urls;
        // app::Crypto crypto;
    };

} // namespace app