#include <magic_enum/magic_enum.hpp>
#include <nlohmann/json.hpp>
#include <format>

#include "config/config.h"
#include "config/base.h"
#include "config/email.h"
#include "config/protocols.h"
#include "config.h"

using json = nlohmann::json;

namespace cfg {
    template <typename T, typename TEmail, typename TMap>
    void add_comms_enitity(json& j, TMap& add_to) {
        for (auto& [name, j_ent] : j.items()) {
            auto type = magic_enum::enum_cast<typename T::Type>(j_ent.at("type").get<std::string>(), magic_enum::case_insensitive);

            if (!type) {
                throw InvalidConfigException(std::format("'{}' is invalid type", j_ent.at("type").get<std::string>()));
            }
            else if (type == T::Type::EMAIL) {
                auto id = T::Id::register_id(name);
                add_to[id] = std::make_shared<const TEmail>(id, j_ent);
            }
        }
    }

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
            // add_attachments(jf["attachments"]);
        }
        else {
            throw InvalidConfigException("Missing attachments");
        }

        if (jf.contains("channels") && jf["channels"].is_object()) {
            add_comms_enitity<Channel, EmailChannel>(jf["channels"], channels);
        }
        else {
            throw InvalidConfigException("Missing channels");
        }

        if (jf.contains("recipients_groups") && jf["recipients_groups"].is_object()) {
            add_comms_enitity<RecipientGroup, EmailRecipientGroup>(jf["recipients_groups"], rgroups);
        }
        else {
            throw InvalidConfigException("Missing recipient groups");
        }

        if (jf.contains("messages") && jf["messages"].is_object()) {
            add_comms_enitity<Message, EmailMessage>(jf["messages"], messages);
        }

        if (jf.contains("protocols") && jf["protocols"].is_object()) {
            add_protocols(jf["protocols"]);
        }
    }

    void Config::add_protocols(json& j_protocols) {
        for (auto& [name, j_p] : j_protocols.items()) {
            auto type = magic_enum::enum_cast<Protocol::Type>(j_p.at("type").get<std::string>(), magic_enum::case_insensitive);

            if (!type) {
                throw InvalidConfigException(std::format("{} is invalid protocol type", j_p.at("type").get<std::string>()));
            }
            else if (type == Protocol::Type::DELAY) {
                auto id = Protocol::Id::register_id(name);
                protocols[id] = std::make_shared<DelayProtocol>(id, j_p);
            }
        }
    }
} // namespace cfg

