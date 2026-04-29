cmake_minimum_required(VERSION 3.16)

project(MegaManX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------
# INCLUDE HEADERS
# ----------------------------
include_directories(${CMAKE_SOURCE_DIR}/include)

# ----------------------------
# SFML (MANUAL INSTALL)
# ----------------------------
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML REQUIRED COMPONENTS
    graphics window system audio
)

# ----------------------------
# TMXLITE SOURCES
# ----------------------------
file(GLOB TMXLITE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/tmxlite/*.cpp
    ${CMAKE_SOURCE_DIR}/src/tmxlite/*.c
    ${CMAKE_SOURCE_DIR}/src/tmxlite/detail/*.cpp
    ${CMAKE_SOURCE_DIR}/src/tmxlite/detail/*.c
)

add_library(tmxlite STATIC ${TMXLITE_SOURCES})

target_include_directories(tmxlite PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# ----------------------------
# EXECUTABLE
# ----------------------------
add_executable(MegaManX
    src/main.cpp
    src/PlayerPhysics.cpp
    src/PlayerMovement.cpp
    src/Camera.cpp
    src/Enemy.cpp
    src/CoinSystem.cpp
    src/Collision.cpp
    src/Combat.cpp
    src/Draw.cpp
    src/GameInit.cpp
    "src/UpdateAnimation.cpp"
    src/TileMap.cpp
)

# ----------------------------
# LINK LIBRARIES
# ----------------------------
target_link_libraries(MegaManX PRIVATE
    tmxlite
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# ----------------------------
# COPY ASSETS
# ----------------------------
file(COPY ${CMAKE_SOURCE_DIR}/assets
     DESTINATION ${CMAKE_BINARY_DIR})
