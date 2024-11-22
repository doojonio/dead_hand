
#include <nlohmann/json.hpp>

#include "config/email.h"
#include "config/config.h"

namespace cfg {
    EmailRecipientGroup::EmailRecipientGroup(RecipientGroup::Id id, json& j) : id(id) {
        auto jemails = j.at("emails");
        if (!jemails.is_array()) {
            throw InvalidConfigException("emails in email recipient group is not an array");
        }

        for (const auto& jemail : jemails) {
            emails.emplace_back(jemail.get<std::string>());
        }
    }

} // namespace cfg
