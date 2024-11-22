#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "config/base.h"

using json = nlohmann::json;

namespace cfg {

    struct DelayProtocol : Protocol {
        Protocol::Id id;
        Protocol::Type type = Protocol::Type::DELAY;
        std::vector<std::string> messages;

        DelayProtocol(Protocol::Id id, json& j) :
            id(std::move(id)) {
            for (auto& msgid : j.at("messages")) {
                messages.emplace_back(msgid.get<std::string>());
            }
        };
    };
} // namespace cfg
