# WebBgfx

This project demonstrates how to use bgfx with Emscripten to create a simple "Hello World" application using OpenGL.

## Project Structure

```
web-bgfx/
├── CMakeLists.txt
├── src/
│   └── main.cpp
├── shaders/
│   ├── vs_cubes.sc
│   └── fs_cubes.sc
└── bgfx.cmake/
```

## Prerequisites

- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)
- [CMake](https://cmake.org/download/)
- [bgfx](https://github.com/bkaradzic/bgfx)
- [GLFW](https://www.glfw.org/)

## Setup

1. Clone the bgfx repository and its dependencies (bx and bimg) into the `bgfx.cmake` directory:
    ```sh
    git clone --recursive https://github.com/bkaradzic/bgfx.cmake bgfx.cmake
    ```

2. Create a `build` directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Configure the project using Emscripten:
    ```sh
    emcmake cmake ..
    ```

4. Build the project:
    ```sh
    emmake make
    ```

## Running

Open the generated `WebBgfx.html` file in a web browser to see the "Hello World" rendered using bgfx and OpenGL.

## Source Code

### `src/main.cpp`

```cpp
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>

void initBgfx(GLFWwindow* window) {
    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL;
    init.resolution.width = 800;
    init.resolution.height = 600;
    init.resolution.reset = BGFX_RESET_VSYNC;
    bgfx::init(init);
}

void renderFrame() {
    bgfx::touch(0);
    bgfx::frame();
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello BGFX", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    initBgfx(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        renderFrame();
        glfwSwapBuffers(window);
    }

    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
```

### `CMakeLists.txt`

```cmake
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
```
