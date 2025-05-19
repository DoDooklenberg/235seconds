cmake_minimum_required(VERSION 3.28)
project(235seconds LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp
    label.h label.cpp
    basemodule.h basemodule.cpp
    drawingmodule.h drawingmodule.cpp
    drawingpoint.h drawingpoint.cpp
    button.h button.cpp
    levermodule.h levermodule.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
