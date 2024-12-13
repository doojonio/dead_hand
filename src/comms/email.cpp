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
    void EmailChannel::send(std::unique_ptr<BaseMessage> bmsg) {
        return send(cast_u<EmailMessage>(std::move(bmsg)));
    }
    void EmailChannel::send(std::shared_ptr<EmailMessage> emsg) {
        std::cout << emsg->subject << std::endl;
        std::cout << emsg->body << std::endl;
        std::cout << emsg->rgroup.get() << std::endl;

        auto rg = registries::rgroups.get(emsg->rgroup);
        auto rgroup = registries::rgroups.get<EmailRecipientGroup>(emsg->rgroup);

        std::cout << rgroup->ser() << std::endl;
        // mailio::message msg;

        // msg.from(mailio::mail_address("dead_hand", email.get()));
        // msg.add_recipient(mailio::mail_address("dead_hand", registries::rgroups.get(emsg->rgroup).emails.at(0).get()));
        // msg.subject(emsg->subject);
        // msg.content(emsg->body);

        // // auto iatstream = std::ifstream(at.url.get_path().value(), std::ios::binary);
        // // std::list<std::tuple<std::istream&, std::string, mailio::message::content_type_t>> atts;
        // // atts.push_back(std::make_tuple(
        // //     std::ref(iatstream), std::string("tzuyu_im.jpg"), mailio::message::content_type_t(mailio::message::media_type_t::IMAGE, "jpg")
        // // ));
        // // msg.attach(atts);

        // conn.submit(msg);
    }
}
