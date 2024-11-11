#include <format>
#include <iostream>

#include <cpr/cpr.h>
#include <magic_enum/magic_enum.hpp>

#include <config/config.h>

#include "cli/cli.h"
#include "in/version.h"

constexpr std::string NAME = "dead_hand";
constexpr std::string INCOMPILED_URL = "file:///asdjkk";

int main(int argc, char* argv[]) {
    app::Cli cli(NAME, std::format("{}.{}", VERSION_MAJOR, VERSION_MINOR));

    try {
        cli.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << cli;
        return 1;
    }

    www::Url cfg_url(INCOMPILED_URL);
    if (auto url = cli.get_url()) {
        cfg_url = url.value();
    }

    cfg::Config config;
    config << cfg_url;

    return 0;
}