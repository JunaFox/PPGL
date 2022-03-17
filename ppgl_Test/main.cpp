#include <ppgl.h>

int main() {
    PPGL::Window window;
    PPGL::Vulkan vulkan;

    window.addWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window.openWindow(800, 600, "test");

    vulkan.init();
    while(window.update()){

    }

    return 0;
}
