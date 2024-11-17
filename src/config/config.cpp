#include <magic_enum/magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <format>

#include "config/config.h"
#include "config/base.h"
#include "config/email.h"
#include "config.h"

using json = nlohmann::json;

namespace cfg {

    void Config::operator<<(www::Url url) {
        auto scheme = url.get_scheme();

        json jf;
        if (scheme == "file") {
            std::ifstream ifs(url.get_path().value());
            jf = json::parse(ifs);
        }
        else if (scheme == "http") {
            // TODO
        }

        if (jf.contains("attachments") && jf["attachments"].is_object()) {
            add_attachments(jf["attachments"]);
        }

        if (jf.contains("channels") && jf["channels"].is_object()) {
            add_channels(jf["channels"]);
        }
        else {
            throw InvalidConfigException("Missing channels");
        }

        if (jf.contains("recipients_groups") && jf["recipients_groups"].is_object()) {
            add_recipients_groups(jf["recipients_groups"]);
        }
        else {
            throw InvalidConfigException("Missing recipient groups");
        }

        if (jf.contains("messages") && jf["messages"].is_object()) {
            add_messages(jf["messages"]);
        }

        if (jf.contains("protocols") && jf["protocols"].is_object()) {
            add_protocols(jf["protocols"]);
        }
    }


    void Config::add_channels(json& j_channels) {
        for (auto& [name, j_ch] : j_channels.items()) {
            auto type = magic_enum::enum_cast<Channel::Type>(j_ch.at("type").get<std::string>(), magic_enum::case_insensitive);

            if (!type) {
                throw InvalidConfigException(std::format("'{}' is invalid channel type", j_ch.at("type").get<std::string>()));
            }
            else if (type == Channel::Type::EMAIL) {
                channels[name] = std::make_shared<const EmailChannel>(j_ch);
            }
        }
    }

    void Config::add_recipients_groups(json& j_rgroups) {
        for (auto& [name, j_gr] : j_rgroups.items()) {
            auto type = magic_enum::enum_cast<RecipientGroup::Type>(j_gr.at("type").get<std::string>(), magic_enum::case_insensitive);

            if (!type) {
                throw InvalidConfigException(std::format("'{}' is invalid recipient group type", j_gr.at("type").get<std::string>()));
            }
            else if (type == RecipientGroup::Type::EMAIL) {
                rgroups[name] = std::make_shared<const EmailRecipientGroup>(j_gr);
            }
        }
    }

    void Config::add_attachments(json& j_attachments) {
    }

    void Config::add_messages(json& j_msgs) {
    }

    void Config::add_protocols(json& j_protocols) {
    }
} // namespace cfg

