#pragma once

namespace protocols
{
    struct BaseProtocol {
        virtual std::string ser() = 0;
        virtual ~BaseProtocol() {};
    };
} // namespace protocols

