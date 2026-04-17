cmake_minimum_required(VERSION 3.16)

project(MegaManX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Executable
add_executable(MegaManX
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerPhysics.cpp
    ${CMAKE_SOURCE_DIR}/src/PlayerMovement.cpp
    ${CMAKE_SOURCE_DIR}/src/Camera.cpp
    ${CMAKE_SOURCE_DIR}/src/Enemy.cpp
    ${CMAKE_SOURCE_DIR}/src/CoinSystem.cpp
    ${CMAKE_SOURCE_DIR}/src/Collision.cpp
    ${CMAKE_SOURCE_DIR}/src/Combat.cpp
    ${CMAKE_SOURCE_DIR}/src/Draw.cpp
    ${CMAKE_SOURCE_DIR}/src/GameInit.cpp
    ${CMAKE_SOURCE_DIR}/src/UpdateAnimation.cpp
)

# SFML path (local override allowed)
if(NOT SFML_DIR)
    set(SFML_DIR "C:/SFML/lib/cmake/SFML")
endif()

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system audio)

target_link_libraries(MegaManX
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# 🔥 CRITICAL: copy assets
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})