#pragma once

#include <format>
#include <memory>

#include <argparse/argparse.hpp>

#include "util/www.h"

class Cli {
public:
    inline Cli(std::string name, std::string version)
        : parser(argparse::ArgumentParser(name, version)) {
        build_args();
    };

    void parse_args(int argc, char* argv[]);

    std::optional<util::Url> get_url() const;

    friend inline auto& operator<<(std::ostream& os, Cli& cli) {
        os << cli.parser;
        return os;
    }

private:
    argparse::ArgumentParser parser;
    void build_args();
};