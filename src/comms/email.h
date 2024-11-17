#pragma once

#include <string>

#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

#include "util/www.h"
#include "util/email.h"

namespace comms {
    class EmailMessage {
        std::string subject;
        std::string body;
    };

    class EmailRecipientsGroup {
    };

    class EmailChannel {
    public:
        enum class AuthMethod { NONE, LOGIN, START_TLS };
        void send(EmailMessage&);
    private:
        www::Host host;
        uint port;
        email::Email auth_email;
        std::string pass;
        AuthMethod method;
    };

} // namespace app
