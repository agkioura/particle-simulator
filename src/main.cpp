#include <iostream>
#include "../include/headers/window/window.h"

#define WIDTH 640
#define HEIGHT 480

GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbfun) {
    printf("sigma");
}

int main() {
    
    Window window(WIDTH, HEIGHT, "Hello World!");

    if (!window.createContext()) {
        return -1;
    }
    
    window.start();
    return 0;
}