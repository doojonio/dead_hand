#pragma once
#include <atomic>

namespace util {

    class AtomicBoolRAII {
    public:
        AtomicBoolRAII(std::atomic<bool>& flag)
            : flag(flag) {
            flag.store(true);
        }

        ~AtomicBoolRAII() {
            flag.store(false);
        }

        AtomicBoolRAII(const AtomicBoolRAII&) = delete;
        AtomicBoolRAII& operator=(const AtomicBoolRAII&) = delete;

    private:
        std::atomic<bool>& flag;
    };
} // namespace util

