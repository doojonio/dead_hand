#include "comms/attachment.h"
#include "comms/email.h"
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <mailio/mime.hpp>
#include <memory>
#include <string>
#include "util/pointers.h"

#include "email.h"
#include <comms/base.h>
#include "registries.h"

namespace comms {

    [[nodiscard]] std::string EmailRecipientGroup::ser() {
        std::vector<std::string> emails_str(emails.size());
        // потому что могу
        std::transform(emails.cbegin(), emails.cend(), emails_str.begin(), [](const auto& e) {return e.get();});
        auto j = json{
            {"name", name},
            {"emails", emails_str},
        };

        return j.dump();
    };

    EmailRecipientGroup::EmailRecipientGroup(const json& j) : name(j.at("name").get<std::string>()) {
        for (auto& e : j["emails"]) {
            emails.emplace_back(e);
        }
    }


    EmailMessage::EmailMessage(const json& j) :
        channel(ChannelId(j.at("channel").get<std::string>())),
        rgroup(RecipientGroupId(j.at("recipient_group").get<std::string>())),
        subject(j.at("subject").get<std::string>()),
        body(j.at("body").get<std::string>()) {
        if (j.at("attachments").is_array()) {
            for (auto& at_id : j.at("attachments")) {
                attachments.emplace_back(at_id.get<std::string>());
            }
        }
    }
    ChannelId EmailMessage::get_channel_id() const {
        return channel;
    }
    ;

    [[nodiscard]] std::string EmailMessage::ser() {
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


    [[nodiscard]] std::string EmailChannel::ser() {
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

    EmailChannel::EmailChannel(const json& j) :
        host(util::www::Host(j.at("host").get<std::string>())),
        port(j.at("port").get<uint>()),
        email(util::www::Email(j.at("email").get<std::string>())),
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

    void EmailChannel::send(std::unique_ptr<BaseMessage> bmsg) {
        return send(util::cast_u<EmailMessage>(std::move(bmsg)));
    }

    void EmailChannel::send(std::shared_ptr<EmailMessage> emsg) {
        auto rgroup = registries::rgroups.get<EmailRecipientGroup>(emsg->rgroup);

        mailio::message msg;

        msg.from(email);
        msg.subject(emsg->subject);
        msg.content(emsg->body);

        for (const auto& email : rgroup->emails) {
            msg.add_recipient(email);
        }

        for (auto& attachment_id : emsg->attachments) {
            auto attachment = registries::attachments.get(attachment_id);

            msg.attach(attachment->get_content(), attachment->name, attachment->mime.get_category(), attachment->mime.get_type());
        }

        conn.submit(msg);
    }
}
