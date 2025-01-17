
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <fstream>
#include "attachment.h"

namespace comms {
    Attachment::Attachment(const json& j) :
        name(j.at("name").get<std::string>()),
        mime(util::www::Mime(j.at("mime").get<std::string>())),
        url(util::www::Url(j.at("url").get<std::string>())) {
        if (j.contains("b64content")) {
            b64content = j.at("b64content").get<std::string>();
        }
        else {
            fetch_content();
        }
    };


    [[nodiscard]] std::string Attachment::ser() {
        auto j = json{
            {"name", name},
            {"mime", mime.get()},
            {"url", url.get()},
            {"b64content", b64content},
        };

        return j.dump();
    }
    void Attachment::fetch_content() {
        auto scheme = url.get_scheme();

        if (!scheme) {
            throw std::invalid_argument("missing file url scheme");
        }

        auto scheme_v = scheme.value();
        if (scheme_v == "file") {
            auto path = url.get_path().value();
            auto fs = CryptoPP::FileSource(path.c_str(), true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(b64content)));
        }
        else {
            throw std::invalid_argument(std::format("cannot fetch from scheme {}", scheme_v));
        }
    }

    std::istringstream Attachment::get_content() {
        CryptoPP::Base64Decoder decoder;
        std::string result;
        CryptoPP::StringSource(b64content, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(result)));

        // Pump the data through the filter
        decoder.MessageEnd();

        // Create an istringstream from the decoded data
        return std::istringstream(result);
    }

} // namespace comms
