#pragma once
#include <unordered_map>
#include <string>

namespace util::wwww {
    enum class MimeType {
        VIDEO_MP4,
    };

    const std::unordered_map<MimeType, std::string> MIME_STRINGS
    {
        {MimeType::VIDEO_MP4, "video/mp4"},
    };
} // namespace util::wwww
