#include "president.h"
#include <thread>
#include <format>
#include <iostream>


auto binary_search_insert_pos(auto& v, auto& time) {
    int n = v.size();
    if (n == 0) {
        return v.begin();
    }
    int i = 0;

    int start = 0;
    int end = n - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        auto& [t, cb] = v.at(mid);

        if (time < t) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return v.begin() + start;
}

void President::rake_new_cbs() {
    std::lock_guard<std::mutex> lock(run_mtx);

    while (!new_cbs.empty()) {
        auto& pair = new_cbs.front();
        cbs.insert(binary_search_insert_pos(cbs, pair.first), pair);
        new_cbs.pop();
    }
}

President:: operator bool() const {
    return !cbs.empty();
};

void President:: operator ()() {
    if (running) {
        throw std::runtime_error("already running");
    }

    // probably million race conditions there but похуй + нахуй this shit, im tired :c
    int i = 0;
    while (!cbs.empty()) {
        std::cout << std::format("iter: {}, ", i++) << std::endl << dump() << std::endl;

        auto [tp, cb] = std::move(cbs.front());
        cbs.erase(cbs.begin());

        std::cout << "sleeping till: " << tp << std::endl;

        std::this_thread::sleep_until(tp);

        {
            std::lock_guard<std::mutex> lock(run_mtx);
            util::AtomicBoolRAII running_raii(running);

            cb(*this);
        }
        rake_new_cbs();
    }
    std::cout << "done" << std::endl;
}

void President::add_job(std::chrono::system_clock::time_point time, President::Job func) {
    new_cbs.emplace(time, func);

    if (!running) {
        rake_new_cbs();
    }
}

std::string President::dump() {
    std::stringstream ss;

    int i = 0;
    for (auto& pair : cbs) {
        ss << "Job " << i++ << " " << pair.first << std::endl;
    }

    return ss.str();
}

std::chrono::system_clock::time_point President::get_tp_from_election(std::chrono::days elapsed_days) {
    return elected_at + elapsed_days;
};
