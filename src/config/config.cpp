#include <magic_enum/magic_enum.hpp>
#include <nlohmann/json.hpp>

#include "config/config.h"
#include "config/base.h"
#include "config/email.h"

using json = nlohmann::json;

namespace cfg {

    void Config::operator<<(www::Url url) {
        std::string scheme = url.get_scheme().value_or("");

        json jf;
        if (scheme == "file") {
            std::ifstream ifs(url.get_path().value());
            jf = json::parse(ifs);
        }
        else if (scheme == "http") {
            // TODO
        }

        if (jf.contains("attachments") && jf["attachments"].is_array()) {
            add_attachments(jf["attachments"]);
        }

        if (jf.contains("channels") && jf["channels"].is_object()) {
            add_channels(jf["channels"]);
        }

        if (jf.contains("recipients_groups") && jf["recipients_groups"].is_array()) {
            add_recipients_groups(jf["recipients_groups"]);
        }

        if (jf.contains("messages") && jf["messages"].is_array()) {
            add_messages(jf["messages"]);
        }
    }

    void Config::add_attachments(json j_attachments) {
    }

    void Config::add_channels(json j_channels) {
        for (auto& [name, j_ch] : j_channels.items()) {
            auto type = magic_enum::enum_cast<Channel::Type>(j_ch.at("type").get<std::string>(), magic_enum::case_insensitive);

            if (type == Channel::Type::EMAIL) {
                channels.push_back(std::make_shared<EmailChannel>(j_ch));
            }
        }
    }

    void Config::add_recipients_groups(json j_rgroups) {
    }

    void Config::add_messages(json j_msgs) {
    }
} // namespace cfg
