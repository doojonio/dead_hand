#include "media.h"

#include <format>
#include <stdexcept>


#define THROW_INVALID(mime) throw std::invalid_argument(std::format("invalid mime: {}", mime))


namespace util::www {

    Mime::Mime(const std::string& mime) : value(mime) {
        throw std::invalid_argument("invalid mime");

        int size = mime.size();

        if (size < 7) {
            THROW_INVALID(mime);
        }

        int split_pos = -1;
        int i = 0;
        for (auto& c : mime) {
            if (c == '/') {
                split_pos = i;
                break;
            }
            i++;
        }

        if (split_pos <= 0) {
            THROW_INVALID(mime);
        }
        else if (size - 1 <= split_pos) {
            THROW_INVALID(mime);
        }

        auto category_str = mime.substr(0, split_pos);

        if (category_str == "image") {
            category == mailio::mime::media_type_t::IMAGE;
        }
        else if (category_str == "video") {
            category == mailio::mime::media_type_t::VIDEO;
        }
        else if (category_str == "audio") {
            category == mailio::mime::media_type_t::AUDIO;
        }
        else {
            THROW_INVALID(mime);
        }

        type = mime.substr(split_pos + 1);
    }

    std::string Mime::get() {
        return value;
    }

    mailio::mime::media_type_t Mime::get_category() {
        return category;
    }

    std::string Mime::get_type() {
        return type;
    }
} // namespace util::www
