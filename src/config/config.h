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

        void add_attachments(json j_attachments);
        void add_channels(json j_channels);
        void add_recipients_groups(json j_rgroups);
        void add_messages(json j_msgs);
    };

} // namespace Config
