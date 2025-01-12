#pragma once
#include <memory>
#include <string>

#include <cstdint>
#include <nlohmann/json.hpp>
#include <ids.h>
#include "protocols/base.h"
#include "president.h"

using json = nlohmann::json;


namespace protocols {
    class DmsgProtocol : public BaseProtocol {
        ProtocolId id;
        uint8_t delay = 0;
        uint8_t repeat = 0;
        uint8_t prolong = 0;
        std::string prolong_secret = "";
        std::vector<MessageId> messages;
    public:
        DmsgProtocol(const json& j);

        void init_president(ProtocolId, President&) override;
        ProtocolId get_id();

        void activate_send_procedure(President&);

        [[nodiscard]] std::string ser();
        template <typename TReturn>
        [[nodiscard]] static std::unique_ptr<TReturn> de(const std::string& s) {
            return std::make_unique<DmsgProtocol>(json::parse(s));
        };

    };
} // namespace protocols

