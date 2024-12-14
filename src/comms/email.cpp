#include "comms/attachment.h"
#include "comms/email.h"
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <mailio/mime.hpp>
#include <memory>
#include <string>
#include "util/pointers.h"

#include <iostream>
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

    [[nodiscard]] std::unique_ptr<EmailRecipientGroup> EmailRecipientGroup::de(const std::string& s) {
        return std::make_unique<EmailRecipientGroup>(json::parse(s));
    };

    [[nodiscard]] std::unique_ptr<BaseRecipientGroup> EmailRecipientGroup::de_base(const std::string& s) {
        return de(s);
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
    };

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

    [[nodiscard]] std::unique_ptr<EmailMessage> EmailMessage::de(const std::string& s) {
        return std::make_unique<EmailMessage>(json::parse(s));
    };

    [[nodiscard]] std::unique_ptr<BaseMessage> EmailMessage::de_base(const std::string& s) {
        return de(s);
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

    [[nodiscard]] std::unique_ptr<EmailChannel> EmailChannel::de(const std::string& s) {
        return std::make_unique<EmailChannel>(json::parse(s));
    };

    [[nodiscard]] std::unique_ptr<BaseChannel> EmailChannel::de_base(const std::string& s) {
        return de(s);
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

        msg.from(mailio::mail_address("dead_hand", email.get()));
        // msg.add_recipient(rgroup->mgroup().members.at(0));
        msg.subject(emsg->subject);
        msg.content(emsg->body);

        // // auto iatstream = std::ifstream(at.url.get_path().value(), std::ios::binary);
        // // std::list<std::tuple<std::istream&, std::string, mailio::message::content_type_t>> atts;
        // // atts.push_back(std::make_tuple(
        // //     std::ref(iatstream), std::string("tzuyu_im.jpg"), mailio::message::content_type_t(mailio::message::media_type_t::IMAGE, "jpg")
        // // ));
        // // msg.attach(atts);

        // conn.submit(msg);
    }
}
