cmake_minimum_required(VERSION 3.15)
project(OpenRouterCLI)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE src)

target_link_libraries(main PRIVATE
    cpr::cpr
    nlohmann_json::nlohmann_json
)
