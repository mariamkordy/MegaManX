cmake_minimum_required(VERSION 3.16)

project(MegaManX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files
include_directories(include)

# Collect all source files
file(GLOB SOURCES
    src/*.cpp
)

# Create executable
add_executable(MegaManX ${SOURCES})

# SFML setup (adjust path if needed)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

target_link_libraries(MegaManX
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)