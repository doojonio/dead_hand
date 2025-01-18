configure_file(in/version.h.in in/version.h)

set(
    DH_LIB_SRC
    ${PROJECT_SOURCE_DIR}/src/cli.cpp
    ${PROJECT_SOURCE_DIR}/src/util/www/email.cpp
    ${PROJECT_SOURCE_DIR}/src/util/www/url.cpp
    ${PROJECT_SOURCE_DIR}/src/util/www/host.cpp
    ${PROJECT_SOURCE_DIR}/src/util/crypto.cpp
    ${PROJECT_SOURCE_DIR}/src/comms/email.cpp
    ${PROJECT_SOURCE_DIR}/src/comms/attachment.cpp
    ${PROJECT_SOURCE_DIR}/src/registries.cpp
    ${PROJECT_SOURCE_DIR}/src/registries_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/protocols/dmsg.cpp
    ${PROJECT_SOURCE_DIR}/src/president.cpp
    ${PROJECT_SOURCE_DIR}/src/util/www/media.cpp
)

set(DH_SRC
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${DH_LIB_SRC}
    PARENT_SCOPE
)

set(
    DH_LIB_SRC
    ${DH_LIB_SRC}
    PARENT_SCOPE
)

