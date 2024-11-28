cmake_minimum_required(VERSION 3.10)

# Set the project name
project(lines)

# Ensure C++11 or later standard
set(CMAKE_CXX_STANDARD 11)

# Find SFML (Homebrew installs SFML in a default path)
find_package(SFML 2.5 REQUIRED graphics window system)

# Add the "includes" folder to the header search paths
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Grab all .cpp files from the "src" folder (assuming you have a "src" folder with .cpp files)
set(SOURCE_FILES main.cpp)

# Add source files from the includes folder (if you have .cpp files there)
FILE(GLOB_RECURSE ADDITIONAL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/includes/*.cpp")

# Append the additional sources to the source files list
list(APPEND SOURCE_FILES ${ADDITIONAL_SOURCES})

# Create the executable
add_executable(main ${SOURCE_FILES})

# Link the SFML libraries to the executable
target_link_libraries(main sfml-graphics sfml-window sfml-system)
