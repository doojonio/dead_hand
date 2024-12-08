#pragma once

#include <string>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <format>
#include "comms/attachment.h"
#include <nlohmann/json.hpp>
#include "comms/exc.h"
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
        std::vector<AttachmentId> attachments;
        EmailMessage(const json& j) :
            channel(ChannelId(j.at("channel").get<std::string>())),
            rgroup(RecipientGroupId(j.at("recipient_group").get<std::string>())),
            subject(j.at("subject").get<std::string>()),
            body(j.at("body").get<std::string>()) {
                if(j.at("attachments").is_array()) {
                    for (auto& at_id : j.at("attachments")) {
                        attachments.emplace_back(at_id.get<std::string>());
                    }
                }
        };
    };

    class EmailChannel {
        static const int DEFAULT_TIMEOUT = 10000;

        util::Host host;
        uint port;
        util::Email email;
        std::string login;
        std::string pass;

        mailio::smtps conn;
    public:
        EmailChannel(const json& j) :
            host(util::Host(j.at("host").get<std::string>())),
            port(j.at("port").get<uint>()),
            email(util::Email(j.at("email").get<std::string>())),
            login(j.at("auth_login").get<std::string>()),
            pass(j.at("auth_pass").get<std::string>()),
            conn(mailio::smtps(
                host.get(),
                port,
                std::chrono::milliseconds(
                    j.at("timeout_ms").is_number()
                    ? j.at("timeout_ms").get<int>()
                    : DEFAULT_TIMEOUT
                ))) {
            mailio::dialog_ssl::ssl_options_t ssl_options;
            ssl_options.method = boost::asio::ssl::context::tls_client;
            ssl_options.verify_mode = boost::asio::ssl::verify_none;
            conn.ssl_options(ssl_options);

            try {
                conn.authenticate(login, pass, mailio::smtps::auth_method_t::LOGIN);
            }
            catch (std::exception& e) {
                std::throw_with_nested(CommunicationException(std::format("failed auth: {}", e.what())));
            }
        }

        void send(const EmailMessage& msg, const EmailRecipientGroup& rg, const Attachment& at);
    };

} // namespace app
