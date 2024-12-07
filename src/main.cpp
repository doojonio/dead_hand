#include <format>
#include <iostream>

#include <cpr/cpr.h>
#include <iostream>
#include <magic_enum/magic_enum.hpp>

#include "cli.h"
#include "in/version.h"
#include "registry.h"

#include "comms/email.h"
#include <nlohmann/json.hpp>

constexpr std::string NAME = "dead_hand";
constexpr std::string INCOMPILED_URL = "file:///asdjkk";

void tttt(const util::Url& url) {
    ChannelId::register_id("ch_email");
    MessageId::register_id("msg_email");
    RecipientGroupId::register_id("rg_email");

    auto j = nlohmann::json::parse(std::ifstream(url.get_path().value()));
    auto ech = comms::EmailChannel(j["channels"]["ch_email"]);
    auto emes = comms::EmailMessage(j["messages"]["msg_email"]);
    auto rg = comms::EmailRecipientGroup(j["recipients_groups"]["rg_email"]);

    ech.send(emes, rg);
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
