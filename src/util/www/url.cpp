#include <format>
#include <stdexcept>

#include "url.h"

#define CURL_PART(name, part)                                       \
    std::optional<std::string> Url::get_##name() const {            \
        char *buf;                                                  \
        if (auto rc = curl_url_get(url, CURLUPART_##part, &buf, 0)) \
        {                                                           \
            return std::nullopt;                                    \
        }                                                           \
        std::string result(buf);                                    \
        curl_free(buf);                                             \
        return std::move(result);                                   \
    }                                                               \

namespace util::www {
    void Url::parse_value() {
        if (curl_url_set(url, CURLUPART_URL, value.c_str(), 0)) {
            throw std::invalid_argument(std::format("invalid url: {}", value));
        }
    }

    cpr::Url Url::get_cpr_url() const {
        return cpr::Url(value);
    }

    std::string Url::get() const {
        return value;
    }

    CURL_PART(scheme, SCHEME)
        CURL_PART(user, USER)
        CURL_PART(password, PASSWORD)
        CURL_PART(host, HOST)
        CURL_PART(port, PORT)
        CURL_PART(path, PATH)
        CURL_PART(query, QUERY)
}