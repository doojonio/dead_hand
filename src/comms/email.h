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
#include "util/email.h"
#include "util/www.h"

using json = nlohmann::json;

namespace comms {

    struct EmailRecipientGroup : public BaseRecipientGroup {
        std::string name;
        std::vector<util::Email> emails;
        [[nodiscard]] std::string ser();
        [[nodiscard]] static std::unique_ptr<EmailRecipientGroup> de(const std::string& s);
        [[nodiscard]] static std::unique_ptr<BaseRecipientGroup> de_base(const std::string& s);
        EmailRecipientGroup(const json& j);
    };

    struct EmailMessage : public BaseMessage {
        ChannelId channel;
        RecipientGroupId rgroup;
        std::string subject;
        std::string body;
        std::vector<AttachmentId> attachments;

        EmailMessage(const json& j);
        [[nodiscard]] std::string ser();
        [[nodiscard]] static std::unique_ptr<EmailMessage> de(const std::string& s);
        [[nodiscard]] static std::unique_ptr<BaseMessage> de_base(const std::string& s);
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
        [[nodiscard]] std::string ser();
        [[nodiscard]] static std::unique_ptr<EmailChannel> de(const std::string& s);
        [[nodiscard]] static std::unique_ptr<BaseChannel> de_base(const std::string& s);
        EmailChannel(const json& j);
        void send(std::unique_ptr<BaseMessage> msg) override;
        void send(std::shared_ptr<EmailMessage> msg);

    };

} // namespace app
