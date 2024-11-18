#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "config/base.h"
#include "util/email.h"
#include "util/www.h"

using json = nlohmann::json;

namespace cfg {

    struct EmailChannel : Channel {
        Channel::Type type = Channel::Type::EMAIL;
        www::Host host;
        uint port;
        email::Email email;
        std::string pass;

        EmailChannel(json& j) :
            host(www::Host(j.at("host").get<std::string>())),
            port(j.at("port").get<uint>()),
            email(email::Email(j.at("auth_email").get<std::string>())),
            pass(j.at("auth_pass").get<std::string>()) {
        }
    };

    struct EmailRecipientGroup : RecipientGroup {
        RecipientGroup::Type type = RecipientGroup::Type::EMAIL;
        std::vector<email::Email> emails;

        EmailRecipientGroup(json& j);
    };

    struct EmailMessage : Message {
        RecipientGroup::Type type = RecipientGroup::Type::EMAIL;
        std::string channel;
        std::string rgroup;
        std::string subject;
        std::string body;
        std::vector<std::string> attachments;

        EmailMessage(json& j) :
            channel(j.at("channel").get<std::string>()),
            rgroup(j.at("recipient_group").get<std::string>()),
            subject(j.at("subject").get<std::string>()),
            body(j.at("body").get<std::string>()) {
        };
    };


} // namespace cfg
