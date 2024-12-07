#pragma once

#include <string>
#include <unordered_map>
#include <regex>

#include <cpr/cpr.h>
#include <curl/curl.h>

namespace util {
    class Host {
    public:
        inline Host(std::string value) : value(value) {
            std::regex re("^[^\\d.][\\w.]+"); // I don't care
            if (!std::regex_match(value, re)) {
                throw std::invalid_argument(std::format("invalid host: {}", value));
            }
        };

        [[nodiscard]] inline std::string get() const {
            return value;
        };
    private:
        std::string value;
    };

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

    enum class MimeType {
        VIDEO_MP4,
    };

    const std::unordered_map<MimeType, std::string> MIME_STRINGS
    {
        {MimeType::VIDEO_MP4, "video/mp4"},
    };
}