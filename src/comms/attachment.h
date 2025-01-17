#pragma once

#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <sstream>

#include "util/www/url.h"
#include "util/www/media.h"

using json = nlohmann::json;

namespace comms {
    struct Attachment {
        std::string name;
        util::www::Mime mime;
        util::www::Url url;
        std::string b64content;

        Attachment(const json& j);

        [[nodiscard]] std::string ser();

        template <typename TReturn>
        [[nodiscard]] static std::unique_ptr<TReturn> de(const std::string& s) {
            return std::make_unique<Attachment>(json::parse(s));
        };

        std::istringstream get_content();

    private:
        void fetch_content();
    };
} // namespace comms
