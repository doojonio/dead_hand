#pragma once
#include "president.h"

namespace protocols
{
    struct BaseProtocol {
        virtual void init_president(ProtocolId, President&) = 0;
        virtual std::string ser() = 0;
        virtual ~BaseProtocol() {};
    };
} // namespace protocols

