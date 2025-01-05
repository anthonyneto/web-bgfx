cmake_minimum_required(VERSION 3.0)
project(WebBgfx)

set(CMAKE_CXX_STANDARD 11)

# Set Emscripten toolchain
if("${CMAKE_CXX_COMPILER}" STREQUAL "em++")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Add bgfx
add_subdirectory(bgfx.cmake)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/bgfx/include)
include_directories(${CMAKE_SOURCE_DIR}/bimg/include)
include_directories(${CMAKE_SOURCE_DIR}/bx/include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} bgfx bx bimg)
