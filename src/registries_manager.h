#include "util/www/url.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class RegistriesManager {
public:
    void setup(const util::www::Url&);
    void setup(const json&);
};

