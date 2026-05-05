cmake_minimum_required(VERSION 3.15)
project(OpenRouterCLI)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(main
    src/main.cpp
    src/api/OpenRouterClient.cpp
    src/tools/ReadTool.cpp
)

target_include_directories(main PRIVATE src)

target_link_libraries(main PRIVATE
    cpr::cpr
    nlohmann_json::nlohmann_json
)
