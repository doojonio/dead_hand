#include "registries_manager.h"
#include "registries.h"

#include "comms/email.h"
#include <stdexcept>
#include <string>
#include "comms/attachment.h"
#include <format>
#include <fstream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void RegistriesManager::setup(const util::www::Url& url) {
    auto scheme_opt = url.get_scheme();

    if (!scheme_opt) {
        throw std::invalid_argument("missing scheme in url");
    }

    auto scheme = scheme_opt.value();
    if (scheme == "file") {
        setup(json::parse(std::ifstream(url.get_path().value())));
    }
    else {
        throw std::invalid_argument(std::format("Unknown scheme {}", scheme));
    }
}

void RegistriesManager::setup(const json& j) {
    for (auto& [key, obj] : j["channels"].items()) {
        auto type = obj.at("type").get<std::string>();
        if (type == "email") {
            registries::channels.add<comms::EmailChannel>(key, obj);
        }
        else {
            throw std::invalid_argument(std::format("{} is invalid channel type", type));
        }
    }

    for (auto& [key, obj] : j["recipients_groups"].items()) {
        auto type = obj.at("type").get<std::string>();
        if (type == "email") {
            registries::rgroups.add<comms::EmailRecipientGroup>(key, obj);
        }
        else {
            throw std::invalid_argument(std::format("{} is invalid recipient group type", type));
        }
    }

    for (auto& [key, obj] : j["attachments"].items()) {
        registries::attachments.add<comms::Attachment>(key, obj);
    }

    for (auto& [key, obj] : j["messages"].items()) {
        auto type = obj.at("type").get<std::string>();
        if (type == "email") {
            registries::messages.add<comms::EmailMessage>(key, obj);
        }
        else {
            throw std::invalid_argument(std::format("{} is invalid message type", type));
        }
    }
}