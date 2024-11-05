#include "cli/cli.h"
#include "util/url.h"


namespace app {
    void Cli::build_args() {
        parser.add_argument("--url").help("preferred base url");
    };

    void Cli::parse_args(int argc, char* argv[]) {
        parser.parse_args(argc, argv);
    };

    std::optional<net::Url> Cli::get_url() {
        if (auto val = parser.present<std::string>("--url")) {
            try {
                return net::Url(val.value());
            }
            catch (net::InvalidUrlException& e) {
                return std::nullopt;
            }
        }

        return std::nullopt;
    }
} // namespace app

