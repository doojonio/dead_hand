#include "dmsg.h"
#include "registries.h"

#include "util/pointers.h"


namespace protocols {

    DmsgProtocol::DmsgProtocol(const json& j) :
        id(ProtocolId(j.at("id").get<std::string>())),
        delay(j.at("delay").get<uint8_t>()),
        repeat(j.at("repeat").get<uint8_t>()),
        prolong(j.at("prolong").get<uint8_t>()),
        prolong_secret(j.at("prolong_secret").get<std::string>()) {

        for (const auto& msgid : j.at("messages")) {
            messages.emplace_back(msgid.get<std::string>());
        }
    }

    void DmsgProtocol::init_president(ProtocolId proto_id, President& presik) {
        presik.add_job(
            presik.get_tp_from_election(std::chrono::days(delay)),
            [proto_id](President& presik) {
                auto proto = util::cast_u<DmsgProtocol>(registries::protocols.get(proto_id));
                proto->activate_send_procedure(presik);
            }
        );
    }

    ProtocolId DmsgProtocol::get_id() {
        return id;
    }

    void DmsgProtocol::activate_send_procedure(President& presik) {
        for (auto& msgid : messages) {
            auto message = registries::messages.get(msgid);
            auto channel = registries::channels.get(message->get_channel_id());
            channel->send(std::move(message));
        }

        if (repeat > 0) {
            presik.add_job(
                std::chrono::system_clock::now() + std::chrono::days(repeat),
                [proto_id = id](President& presik) {
                    auto proto = util::cast_u<DmsgProtocol>(registries::protocols.get(proto_id));
                    proto->activate_send_procedure(presik);
                }
            );
        }
    }


    [[nodiscard]] std::string DmsgProtocol::ser() {
        std::vector<std::string> jmsgs;
        jmsgs.reserve(messages.size());


        for (const auto& m : messages) {
            jmsgs.push_back(m.get());
        }

        auto j = json{
            {"id", id.get()},
            {"delay", delay},
            {"repeat", repeat},
            {"prolong", prolong},
            {"prolong_secret", prolong_secret},
            {"messages", jmsgs},
        };
        return j.dump();
    }
} // namespace protocols
