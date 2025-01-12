configure_file(in/version.h.in in/version.h)

set(
    DH_SRC

    src/main.cpp
    src/cli.cpp
    src/util/www/email.cpp
    src/util/www/url.cpp
    src/util/www/host.cpp
    src/util/crypto.cpp
    src/comms/email.cpp
    src/comms/attachment.cpp
    src/registries.cpp
    src/registries_manager.cpp
    src/protocols/dmsg.cpp
    src/president.cpp

    PARENT_SCOPE
)
