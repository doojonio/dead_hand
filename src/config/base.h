#pragma once

#include <format>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace cfg {
    template <typename TId>
    class CfgId {
        std::string value;

    protected:
        static std::unordered_set<std::string> registered_ids;

    public:
        CfgId() : value("") {};

        CfgId(std::string id) : value(id) {
            if (id == "" || registered_ids.find(id) == registered_ids.end()) {
                throw std::invalid_argument(std::format("id {} is empty or not registered", id));
            }
        };

        static TId register_id(std::string id) {
            if (id == "" || registered_ids.find(id) != registered_ids.end()) {
                throw std::invalid_argument(std::format("id {} is empty or already registered", id));
            }

            registered_ids.insert(id);

            return TId(id);
        };

        std::string get() { assert(value != ""); return value; }
    };
    template <typename TId>
    std::unordered_set<std::string> CfgId<TId>::registered_ids;

    struct Channel {
        enum class Type {
            EMAIL
        };
        class Id : public CfgId<Channel::Id> {
            // static std::unordered_set<std::string> registered_ids;
        };

        Channel::Id id;
        Channel::Type type;

        virtual ~Channel() {}
    };

    struct RecipientGroup {
        enum class Type {
            EMAIL
        };
        class Id : public CfgId<RecipientGroup::Id> {
        // protected:
            // static std::unordered_set<std::string> registered_ids;
        };

        RecipientGroup::Id id;
        RecipientGroup::Type type;

        virtual ~RecipientGroup() {}
    };

    struct Message {
        enum class Type {
            EMAIL
        };
        class Id : public CfgId<Message::Id> {
        // protected:
            // static std::unordered_set<std::string> registered_ids;
        };

        Message::Id id;
        Message::Type type;
        Channel::Id channel;
        RecipientGroup::Id rgroup;
        std::vector<std::string> attachments;

        virtual ~Message() {}

    };
} // namespace cfg