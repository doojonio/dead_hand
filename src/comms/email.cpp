#include "comms/attachment.h"
#include "comms/email.h"
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <mailio/mime.hpp>

#include <iostream>

namespace comms {
    void EmailChannel::send(const EmailMessage& emessage, const EmailRecipientGroup& rg, const Attachment& at) {
        mailio::message msg;

        msg.from(mailio::mail_address("dead_hand", email.get()));
        msg.add_recipient(mailio::mail_address("dead_hand", rg.emails.at(0).get()));
        msg.subject(emessage.subject);
        msg.content(emessage.body);

        auto iatstream = std::ifstream(at.url.get_path().value(), std::ios::binary);
        std::list<std::tuple<std::istream&, std::string, mailio::message::content_type_t>> atts;
        atts.push_back(std::make_tuple(
            std::ref(iatstream), std::string("tzuyu_im.jpg"), mailio::message::content_type_t(mailio::message::media_type_t::IMAGE, "jpg")
        ));
        msg.attach(atts);

        conn.submit(msg);
    }
}
