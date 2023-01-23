cmake_minimum_required(VERSION 3.16)

project(tradeprocessor LANGUAGES CXX C VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/71140c3ca7a87bb1b5b9c9f1500fea8858cce344.zip
)

FetchContent_MakeAvailable(googletest)

include(CTest)

add_subdirectory(lib)
add_subdirectory(tests)
add_subdirectory(tradeprocessor)

install(DIRECTORY DESTINATION "${PROJECT_SOURCE_DIR}/bin/")