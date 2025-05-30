cmake_minimum_required(VERSION 3.28)
project(235seconds LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_1.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_1_cut.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_2.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_2_cut.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_3.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_3_cut.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_4.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireSprite_4_cut.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY BackPlate.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY FrontPlate.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY font.ttf DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY qr.png DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY WireCut.wav DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY LeverFlip.wav DESTINATION ${CMAKE_BINARY_DIR}/bin)

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
    wiresmodule.cpp wiresmodule.h
    drawwires.cpp drawwires.h
    button.h button.cpp
    drawingmodule.cpp drawingmodule.h
    drawingpoint.cpp drawingpoint.h
    particlesystem.h particlesystem.cpp
    levermodule.h levermodule.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
target_link_libraries(main PRIVATE SFML::Audio)
