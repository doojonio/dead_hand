include(GoogleTest)

function(add_dh_test SOURCE_FILE)
    get_filename_component(file_name ${SOURCE_FILE} NAME_WE)

    add_executable(
        ${file_name}
        ${SOURCE_FILE}
        ${DH_LIB_SRC}
    )

    target_link_libraries(
        ${file_name}
        PUBLIC
            GTest::gtest_main
            nlohmann_json::nlohmann_json
            cpr::cpr
            CURL::libcurl
            magic_enum::magic_enum
            mailio
            cryptopp
    )

    target_include_directories(
        ${file_name}
        PUBLIC
            ${PROJECT_BINARY_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/../src
    )

    gtest_discover_tests(${file_name})

endfunction(add_dh_test)

file(GLOB tfiles ${CMAKE_CURRENT_SOURCE_DIR}/test*.cpp)
foreach(file_name ${tfiles})
    add_dh_test(${file_name})
endforeach(file_name ${tfiles})

