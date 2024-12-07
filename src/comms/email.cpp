#include "comms/email.h"
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>

#include <iostream>

namespace comms {
    void EmailChannel::send(const EmailMessage& emessage, const EmailRecipientGroup& rg) const {
        mailio::message msg;

        msg.from(mailio::mail_address("dead_hand", email.get()));
        msg.add_recipient(mailio::mail_address("dead_hand", rg.emails.at(0).get()));
        msg.subject(emessage.subject);
        msg.content(emessage.body);

        std::cout << "AAA" << std::endl;
        mailio::smtps conn(host.get(), port, std::chrono::milliseconds(1000));

        mailio::dialog_ssl::ssl_options_t ssl_options;
        ssl_options.method = boost::asio::ssl::context::tls_client;
        ssl_options.verify_mode = boost::asio::ssl::verify_none;
        conn.ssl_options(ssl_options);
        // mailio::smtps::ssl_options(mailio::dialog_ssl::ssl_options_t:);

        // std::cout << format("BBB {} {} {} {}", host.get(), port, login, pass) << std::endl;
        conn.authenticate(login, pass, mailio::smtps::auth_method_t::LOGIN);

        std::cout << "CCC" << std::endl;

        conn.submit(msg);
        std::cout << "DDD" << std::endl;
    }
}
