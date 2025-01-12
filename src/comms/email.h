#pragma once

#include <algorithm>
#include <format>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <mailio/mailboxes.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

#include "comms/attachment.h"
#include "comms/base.h"
#include "comms/exc.h"
#include "ids.h"
#include "util/www/email.h"
#include "util/www/host.h"

using json = nlohmann::json;

namespace comms {

    struct EmailRecipientGroup : public BaseRecipientGroup {
        std::string name;
        std::vector<util::www::Email> emails;
        [[nodiscard]] std::string ser();
        EmailRecipientGroup(const json& j);

        template<typename TReturn>
        [[nodiscard]] static std::unique_ptr<TReturn> de(const std::string& s) {
            return std::make_unique<EmailRecipientGroup>(json::parse(s));
        };

    };

    struct EmailMessage : public BaseMessage {
        ChannelId channel;
        RecipientGroupId rgroup;
        std::string subject;
        std::string body;
        std::vector<AttachmentId> attachments;

        EmailMessage(const json& j);

        ChannelId get_channel_id() const override;

        [[nodiscard]] std::string ser();
        template <typename TReturn>
        [[nodiscard]] static std::unique_ptr<TReturn> de(const std::string& s) {
            return std::make_unique<EmailMessage>(json::parse(s));
        };

    };

    class EmailChannel : public BaseChannel {
        static const int DEFAULT_TIMEOUT = 10000;

        util::www::Host host;
        uint port;
        util::www::Email email;
        std::string login;
        std::string pass;
        int timeout_ms;
        mailio::smtps conn;
    public:
        [[nodiscard]] std::string ser();
        EmailChannel(const json& j);
        void send(std::unique_ptr<BaseMessage> msg) override;
        void send(std::shared_ptr<EmailMessage> msg);

        template <typename TReturn>
        [[nodiscard]] static std::unique_ptr<TReturn> de(const std::string& s) {
            return std::make_unique<EmailChannel>(json::parse(s));
        };

    };

} // namespace app
