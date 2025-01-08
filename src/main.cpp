#include <format>

#include <memory>
#include <cpr/cpr.h>
#include <magic_enum/magic_enum.hpp>

#include "cli.h"
#include "in/version.h"
#include "ids.h"

#include "registries.h"

#include "comms/email.h"
#include <nlohmann/json.hpp>

#include "registries_manager.h"

constexpr std::string NAME = "dead_hand";
constexpr std::string INCOMPILED_URL = "file:///asdjkk";

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

    util::www::Url cfg_url(INCOMPILED_URL);
    if (auto url = cli.get_url()) {
        cfg_url = url.value();
    }

    RegistriesManager mng;

    mng.setup(cfg_url);

    auto p = ProtocolId(std::string("all_in"));
    registries::protocols_dmsg.get(
        p
    );

    return 0;
}
