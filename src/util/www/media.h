#pragma once
#include <unordered_map>
#include <string>

#include <mailio/mime.hpp>

namespace util::www {

    class Mime {
        std::string value;
        mailio::mime::media_type_t category;
        std::string type;
    public:
        Mime(const std::string& mime);

        std::string get();

        mailio::mime::media_type_t get_category();

        std::string get_type();
    };

} // namespace util::wwww
