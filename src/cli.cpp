#include "cli.h"
#include "util/www.h"


Cli::Cli(std::string name, std::string version)
    : parser(argparse::ArgumentParser(name, version)) {
    build_args();
};

void Cli::build_args() {
    parser.add_argument("--url").help("preferred base url");
};

void Cli::parse_args(int argc, char* argv[]) {
    parser.parse_args(argc, argv);
};

std::optional<util::Url> Cli::get_url() const {
    if (auto val = parser.present<std::string>("--url")) {
        try {
            return util::Url(val.value());
        }
        catch (std::invalid_argument& e) {
            return std::nullopt;
        }
    }

    return std::nullopt;
}

