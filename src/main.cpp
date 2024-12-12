#include <format>
#include <iostream>

#include <memory>
#include <cpr/cpr.h>
#include <iostream>
#include <magic_enum/magic_enum.hpp>

#include "cli.h"
#include "in/version.h"
#include "ids.h"

#include "registries.h"

#include "comms/email.h"
#include <nlohmann/json.hpp>

constexpr std::string NAME = "dead_hand";
constexpr std::string INCOMPILED_URL = "file:///asdjkk";

void tttt(const util::Url& url) {
    auto j = nlohmann::json::parse(std::ifstream(url.get_path().value()));
    registries::channels.add("ch_email", std::make_unique<comms::EmailChannel>(j["channels"]["ch_email"]), comms::EmailChannel::de_base);
    registries::rgroups.add("rg_email", std::make_unique<comms::EmailRecipientGroup>(j["recipients_groups"]["rg_email"]), comms::EmailRecipientGroup::de_base);
    AttachmentId::register_id("tzuyu_image.jpg");
    registries::messages.add("msg_email", std::make_unique<comms::EmailMessage>(j["messages"]["msg_email"]), comms::EmailMessage::de_base);

    // MessageId::register_id("msg_email");
    // RecipientGroupId::register_id("rg_email");

    auto ch = registries::channels.get(ChannelId(std::string("ch_email")));
    auto rg = registries::rgroups.get(RecipientGroupId(std::string("rg_email")));
    // auto msg = registries::messages.get(MessageId(std::string("ch_email")));
    // auto att = comms::Attachment(j["attachments"]["tzuyu_image.jpg"]);
    // auto ech = comms::EmailChannel(j["channels"]["ch_email"]);
    // auto emes = comms::EmailMessage(j["messages"]["msg_email"]);
    // auto rg = comms::EmailRecipientGroup();

    ch->send(registries::messages.get(MessageId(std::string("msg_email"))));
}

int main(int argc, char* argv[]) {
    Cli cli(NAME, std::format("{}.{}", VERSION_MAJOR, VERSION_MINOR));

    try {
        cli.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << cli;
        return 1;
    }

    util::Url cfg_url(INCOMPILED_URL);
    if (auto url = cli.get_url()) {
        cfg_url = url.value();
    }

    tttt(cfg_url);

    return 0;
}
