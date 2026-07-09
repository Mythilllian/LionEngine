cmake_minimum_required(VERSION 3.12)

project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(nlohmann_json 3.12.0 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(
    GameEngine
    ${SOURCES}
)

target_link_libraries(
    GameEngine
    PRIVATE 
    SDL2::SDL2
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
    nlohmann_json::nlohmann_json
)

target_include_directories(
    GameEngine
    PRIVATE 
    include
)