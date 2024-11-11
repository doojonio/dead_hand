#pragma once

#include <string>

#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

#include "base/channel.h"
#include "base/message.h"
#include "util/www.h"
#include "util/email.h"

namespace comms {
    class EmailChannel : public Channel {
    public:
        enum class AuthMethod {NONE, LOGIN, STARTTLS};

        void send_message(Message&) override;
    private:
        ChannelType type = ChannelType::EMAIL;
        www::Host host;
        uint port;
        email::Email auth_email;
        std::string pass;
        AuthMethod method;
    };

    class EmailMessage : Message {
        MessageType type = MessageType::EMAIL;
        std::string subject;
        std::string body;
    };
} // namespace app
