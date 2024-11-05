#pragma once

#include <string>
#include <unordered_map>

namespace net {
    enum class MimeType {
        VIDEO_MP4,
    };

    const std::unordered_map<MimeType, std::string> MIME_STRINGS
    {
        {MimeType::VIDEO_MP4, "video/mp4"},
    };
} // namespace net
