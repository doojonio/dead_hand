configure_file(in/version.h.in in/version.h)

set(
    DH_SRC

    src/main.cpp
    src/cli/cli.cpp
    src/config/config.cpp
    src/util/www.cpp
    src/util/email.cpp

    PARENT_SCOPE
)
