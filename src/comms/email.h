#pragma once

#include <string>

#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <nlohmann/json.hpp>
#include "ids.h"
#include "util/www.h"
#include "util/email.h"

using json = nlohmann::json;

namespace comms {

    struct EmailRecipientGroup {
        std::vector<util::Email> emails;
        EmailRecipientGroup(const json& j) {
            for (auto& e : j["emails"]) {
                emails.emplace_back(e);
            }
        }
    };

    struct EmailMessage {
        ChannelId channel;
        RecipientGroupId rgroup;
        std::string subject;
        std::string body;
        std::vector<std::string> attachments;
        EmailMessage(const json& j) :
            channel(ChannelId(j.at("channel").get<std::string>())),
            rgroup(RecipientGroupId(j.at("recipient_group").get<std::string>())),
            subject(j.at("subject").get<std::string>()),
            body(j.at("body").get<std::string>()) {
        };
    };

    class EmailChannel {
        util::Host host;
        uint port;
        util::Email email;
        std::string login;
        std::string pass;

    public:
        EmailChannel(const json& j) :
            host(util::Host(j.at("host").get<std::string>())),
            port(j.at("port").get<uint>()),
            email(util::Email(j.at("email").get<std::string>())),
            login(j.at("auth_login").get<std::string>()),
            pass(j.at("auth_pass").get<std::string>()) {
        }

        void send(const EmailMessage& msg, const EmailRecipientGroup& rg) const;
    };

} // namespace app
