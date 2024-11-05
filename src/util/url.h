#pragma once

#include <string>

#include <cpr/cpr.h>
#include <curl/curl.h>

namespace net {
    class InvalidUrlException : public std::exception {
    public:
        InvalidUrlException(std::string url) : message("Invalid URL: " + url) {};

        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };

    class Url {
    public:
        Url(std::string value_) : value(std::move(value_)) {
            parse_value();
        }

        cpr::Url get_cpr_url();

        std::optional<std::string> get_scheme();
        std::optional<std::string> get_user();
        std::optional<std::string> get_password();
        std::optional<std::string> get_host();
        std::optional<std::string> get_port();
        std::optional<std::string> get_path();
        std::optional<std::string> get_query();

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
}