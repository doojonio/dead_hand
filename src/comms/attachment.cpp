
#include "attachment.h"

namespace comms {
    Attachment::Attachment(const json& j) :
        mime(j.at("mime").get<std::string>()),
        url(util::www::Url(j.at("url").get<std::string>())) {
    };


    [[nodiscard]] std::string Attachment::ser() {
        auto j = json{
            {"mime", mime},
            {"url", url.get()},
        };

        return j.dump();
    };

} // namespace comms