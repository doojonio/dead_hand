#include "config.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#include <iostream>
namespace cfg {

    void Config::operator<<(www::Url url) {
        std::string scheme = url.get_scheme().value_or("");

        if (scheme == "file") {
            std::ifstream ifs(url.get_path().value());
            json jf = json::parse(ifs);

            std::cout << jf["version"] << std::endl;
        }
        else if (scheme == "http") {
        }
    }
} // namespace cfg
