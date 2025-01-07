include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG bb01c8db702fb41e5497aee9c0559ddf4bf13749)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(magic_enum GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
                                GIT_TAG a72a0536c716fdef4f029fb43e1fd7e7b3d9ac9b)
FetchContent_MakeAvailable(magic_enum)

FetchContent_Declare(mailio GIT_REPOSITORY https://github.com/karastojko/mailio.git
                                GIT_TAG 8a3b92361d244dbb1af722d1ad6dcaf321907936)
FetchContent_MakeAvailable(mailio)

FetchContent_Declare(
  cryptopp
  GIT_REPOSITORY https://github.com/weidai11/cryptopp.git
  GIT_TAG        CRYPTOPP_8_9_0 # or any other version you want to use
)
FetchContent_MakeAvailable(cryptopp)

FetchContent_Declare(
  eventpp
  GIT_REPOSITORY https://github.com/wqking/eventpp
  GIT_TAG        v0.1.3
)
FetchContent_MakeAvailable(eventpp)
