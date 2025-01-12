#pragma once

#include <chrono>
#include <functional>
#include <vector>
#include <utility>
#include <atomic>
#include <queue>
#include <mutex>

#include "util/raii.h"

class President {
    std::chrono::system_clock::time_point
        elected_at = std::chrono::system_clock::now();


    using Job = std::function<void(President&)>;
    using ElemPair = std::pair<std::chrono::system_clock::time_point, Job>;
    std::vector<ElemPair> cbs;
    std::queue<ElemPair> new_cbs;
    std::atomic<bool> running = false;
    std::mutex run_mtx;

    void rake_new_cbs();
public:
    President() = default;
    operator bool() const;
    void operator ()();
    void add_job(std::chrono::system_clock::time_point, Job);

    std::chrono::system_clock::time_point
        get_tp_from_election(std::chrono::days elapsed_days);
};
