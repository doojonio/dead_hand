#pragma once

#include <cpr/cpr.h>
#include <string>
#include <curl/curl.h>

namespace util::www {
    class Url {
    public:
        inline Url(std::string value_) : value(std::move(value_)) {
            parse_value();
        }

        [[nodiscard]] cpr::Url get_cpr_url() const;
        [[nodiscard]] std::string get() const;
        [[nodiscard]] std::optional<std::string> get_scheme() const;
        [[nodiscard]] std::optional<std::string> get_user() const;
        [[nodiscard]] std::optional<std::string> get_password() const;
        [[nodiscard]] std::optional<std::string> get_host() const;
        [[nodiscard]] std::optional<std::string> get_port() const;
        [[nodiscard]] std::optional<std::string> get_path() const;
        [[nodiscard]] std::optional<std::string> get_query() const;

        friend inline auto& operator<<(std::ostream& os, Url& url) {
            os << url.value;
            return os;
        }

        friend inline auto& operator<<(std::ostream& os, Url&& url) {
            os << url.value;
            return os;
        }

    private:
        CURLU* url = curl_url();
        std::string value;

        void parse_value();
    };


} // namespace www::util
