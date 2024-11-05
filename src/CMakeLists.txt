configure_file(in/version.h.in in/version.h)

set(
    DH_SRC

    src/main.cpp
    src/cli/cli.cpp
    src/config/config.cpp
    src/util/url.cpp

    PARENT_SCOPE
)
