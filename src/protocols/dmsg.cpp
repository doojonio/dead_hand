#include "dmsg.h"
#include "registries.h"

#include "util/pointers.h"


namespace protocols {

    DmsgProtocol::DmsgProtocol(const json& j) :
        delay(j.at("delay").get<uint8_t>()),
        repeat(j.at("repeat").get<uint8_t>()),
        prolong(j.at("prolong").get<uint8_t>()),
        prolong_secret(j.at("prolong_secret").get<std::string>()) {

        for (const auto& msgid : j.at("messages")) {
            messages.emplace_back(msgid.get<std::string>());
        }
        for (const auto& msgid : j.at("alert_messages")) {
            alert_messages.emplace_back(msgid.get<std::string>());
        }
    }

    void DmsgProtocol::init_president(ProtocolId proto_id, President& presik) {
        presik.add_job(
            presik.get_tp_from_election(std::chrono::days(delay)),
            [proto_id](President&) {
                auto proto = util::cast_u<DmsgProtocol>(registries::protocols.get(proto_id));
                proto->activate_send_procedure();
            }
        );
    }

    void DmsgProtocol::activate_send_procedure() {
        for (auto& msgid : messages) {
            auto message = registries::messages.get(msgid);
            auto channel = registries::channels.get(message->get_channel_id());
            channel->send(std::move(message));
        }
    }


    [[nodiscard]] std::string DmsgProtocol::ser() {
        std::vector<std::string> jmsgs;
        jmsgs.reserve(messages.size());

        std::vector<std::string> jalert_msgs;
        jalert_msgs.reserve(alert_messages.size());

        for (const auto& m : messages) {
            jmsgs.push_back(m.get());
        }
        for (const auto& m : alert_messages) {
            jalert_msgs.push_back(m.get());
        }

        auto j = json{
            {"delay", delay},
            {"repeat", repeat},
            {"prolong", prolong},
            {"prolong_secret", prolong_secret},
            {"messages", jmsgs},
            {"alert_messages", jalert_msgs}
        };
        return j.dump();
    }
} // namespace protocols
