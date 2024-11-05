#include <format>
#include <iostream>

#include <cpr/cpr.h>
#include <magic_enum/magic_enum.hpp>

#include "cli/cli.h"
#include "in/version.h"

constexpr std::string NAME = "dead_hand";

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

    if (auto url = cli.get_url()) {
        std::cout << url.value() << std::endl;
    }

    return 0;
}