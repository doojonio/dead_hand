#include "dmsg.h"


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
