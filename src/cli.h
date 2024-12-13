#pragma once

#include <format>
#include <memory>

#include <argparse/argparse.hpp>

#include "util/www.h"

class Cli {
    argparse::ArgumentParser parser;
    void build_args();
public:
    Cli(std::string name, std::string version);
    void parse_args(int argc, char* argv[]);
    std::optional<util::Url> get_url() const;

    friend auto& operator<<(std::ostream& os, Cli& cli) {
        os << cli.parser;
        return os;
    }
};