#pragma once

#include <string>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <config/base.h>
#include "util/www.h"

using json = nlohmann::json;

namespace cfg {
    class InvalidConfigException : public std::exception {
    public:
        InvalidConfigException(std::string message) : message("Invalid config: " + message) {};

        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };


    class Config {
    public:
        void operator<<(www::Url content);

    private:
        std::unordered_map<Channel::Id, std::shared_ptr<const Channel>, CfgIdHash<Channel::Id>> channels;
        std::unordered_map<RecipientGroup::Id, std::shared_ptr<const RecipientGroup>, CfgIdHash<RecipientGroup::Id>> rgroups;
        // std::unordered_map<std::string, std::shared_ptr<const Attachment>> attachments;
        std::unordered_map<Message::Id, std::shared_ptr<const Message>, CfgIdHash<Message::Id>> messages;
        std::unordered_map<Protocol::Id, std::shared_ptr<const Protocol>, CfgIdHash<Protocol::Id>> protocols;

        void add_protocols(json& j_protocols);
    };

} // namespace Config
