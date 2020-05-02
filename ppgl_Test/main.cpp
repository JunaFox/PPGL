#include <iostream>
#include <ppgl.h>

int main() {
    PPGL::Window window;
    window.openWindow(600, 600, "test");

    while(window.update()){

    }

    return 0;
}
