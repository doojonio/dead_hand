configure_file(in/version.h.in in/version.h)

set(
    DH_SRC

    src/main.cpp
    src/cli.cpp
    src/util/www.cpp
    src/util/email.cpp
    src/util/crypto.cpp
    src/comms/email.cpp
    src/registries.cpp

    PARENT_SCOPE
)
