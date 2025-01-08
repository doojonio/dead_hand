#include "util/www/url.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class RegistriesManager {
    void setup_channels(const json& j);
    void setup_rgroups(const json& j);
    void setup_attachments(const json& j);
    void setup_messages(const json& j);
    void setup_protocols(const json& j);
public:
    void setup(const util::www::Url&);
    void setup(const json&);
};

