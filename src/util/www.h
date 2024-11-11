#pragma once

#include <string>
#include <unordered_map>
#include <regex>

#include <cpr/cpr.h>
#include <curl/curl.h>

namespace www {
    class InvalidUrlException : public std::exception {
    public:
        InvalidUrlException(std::string url) : message("Invalid URL: " + url) {};

        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };

    class InvalidHostException : public std::exception {
    public:
        InvalidHostException(std::string host) : message("Invalid HOST: " + host) {};

        const char* what() const noexcept override {
            return message.c_str();
        }

    private:
        std::string message;
    };


    class Host {
    public:
        Host(std::string value) : value(value) {
            std::regex re("^[^\\d.][\\w.]+"); // I don't care
            if (!std::regex_match(value, re)) {
                throw InvalidHostException(value);
            }
        };

        std::string get() {
            return value;
        };
    private:
        std::string value;
    };

    class Url {
    public:
        Url(std::string value_) : value(std::move(value_)) {
            parse_value();
        }

        cpr::Url get_cpr_url();
        std::string get();

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

    enum class MimeType {
        VIDEO_MP4,
    };

    const std::unordered_map<MimeType, std::string> MIME_STRINGS
    {
        {MimeType::VIDEO_MP4, "video/mp4"},
    };
}