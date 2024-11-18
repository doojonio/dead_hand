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
        std::unordered_map<std::string, std::shared_ptr<const Channel>> channels;
        std::unordered_map<std::string, std::shared_ptr<const RecipientGroup>> rgroups;
        // std::unordered_map<std::string, std::shared_ptr<const Attachment>> attachments;
        std::unordered_map<std::string, std::shared_ptr<const Message>> messages;

        void add_protocols(json& j_protocols);
    };

} // namespace Config
