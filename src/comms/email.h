#pragma once

#include <string>
#include <algorithm>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <format>
#include "comms/attachment.h"
#include <nlohmann/json.hpp>
#include "comms/exc.h"
#include "ids.h"
#include "util/www.h"
#include <memory>
#include "util/email.h"
#include "util/serializable.h"
#include "comms/base.h"

using json = nlohmann::json;

namespace comms {

    struct EmailRecipientGroup : public BaseRecipientGroup {
        std::vector<util::Email> emails;
        [[nodiscard]] inline std::string ser() {
            std::vector<std::string> emails_str(emails.size());
            // потому что могу
            std::transform(emails.cbegin(), emails.cend(), emails_str.begin(), [](const auto& e) {return e.get();});
            auto j = json{
                {"emails", emails_str},
            };

            return j.dump();
        };

        [[nodiscard]] static std::unique_ptr<EmailRecipientGroup> de(const std::string& s) {
            return std::make_unique<EmailRecipientGroup>(json::parse(s));
        };

        [[nodiscard]] static std::unique_ptr<BaseRecipientGroup> de_base(const std::string& s) {
            return de(s);
        };
        EmailRecipientGroup(const json& j) {
            for (auto& e : j["emails"]) {
                emails.emplace_back(e);
            }
        }
    };

    struct EmailMessage : public BaseMessage {
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
            if (j.at("attachments").is_array()) {
                for (auto& at_id : j.at("attachments")) {
                    attachments.emplace_back(at_id.get<std::string>());
                }
            }
        };
        [[nodiscard]] inline std::string ser() {
            std::vector<std::string> at_str(attachments.size());
            // потому что могу
            std::transform(attachments.cbegin(), attachments.cend(), at_str.begin(), [](const auto& a) {return a.get();});
            auto j = json{
                {"channel", channel.get()},
                {"recipient_group", rgroup.get()},
                {"subject", subject},
                {"body", body},
                {"attachments", at_str},
            };

            return j.dump();
        };

        [[nodiscard]] static std::unique_ptr<EmailMessage> de(const std::string& s) {
            return std::make_unique<EmailMessage>(json::parse(s));
        };

        [[nodiscard]] static std::unique_ptr<BaseMessage> de_base(const std::string& s) {
            return de(s);
        };
    };

    class EmailChannel : public BaseChannel {
        static const int DEFAULT_TIMEOUT = 10000;

        util::Host host;
        uint port;
        util::Email email;
        std::string login;
        std::string pass;
        int timeout_ms;
        mailio::smtps conn;
    public:
        [[nodiscard]] inline std::string ser() {
            auto j = json{
                {"host", host.get()},
                {"port", port},
                {"email", email.get()},
                {"auth_login", login},
                {"auth_pass", pass},
                {"timeout_ms", timeout_ms},
            };

            return j.dump();
        };

        [[nodiscard]] static std::unique_ptr<EmailChannel> de(const std::string& s) {
            return std::make_unique<EmailChannel>(json::parse(s));
        };

        [[nodiscard]] static std::unique_ptr<BaseChannel> de_base(const std::string& s) {
            return de(s);
        };

        EmailChannel(const json& j) :
            host(util::Host(j.at("host").get<std::string>())),
            port(j.at("port").get<uint>()),
            email(util::Email(j.at("email").get<std::string>())),
            login(j.at("auth_login").get<std::string>()),
            pass(j.at("auth_pass").get<std::string>()),
            timeout_ms(
                j.contains("timeout_ms") &&
                j.at("timeout_ms").is_number()
                ? j.at("timeout_ms").get<int>()
                : DEFAULT_TIMEOUT
            ),
            conn(mailio::smtps(
                host.get(),
                port,
                std::chrono::milliseconds(
                    timeout_ms
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

        void send(std::unique_ptr<BaseMessage> msg) override;

    };

} // namespace app
