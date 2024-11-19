#include "cli/cli.h"
#include "util/www.h"


namespace app {
    void Cli::build_args() {
        parser.add_argument("--url").help("preferred base url");
    };

    void Cli::parse_args(int argc, char* argv[]) {
        parser.parse_args(argc, argv);
    };

    std::optional<www::Url> Cli::get_url() {
        if (auto val = parser.present<std::string>("--url")) {
            try {
                return www::Url(val.value());
            }
            catch (std::invalid_argument& e) {
                return std::nullopt;
            }
        }

        return std::nullopt;
    }
} // namespace app

