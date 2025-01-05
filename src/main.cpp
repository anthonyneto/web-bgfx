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
