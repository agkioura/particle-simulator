#include "../include/headers/window/window.h"

#include <iostream>

Window::Window(int width, int height, const char* title) {
    this->width = width;
    this->height = height;
    this->title = title;
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

int Window::createContext() {
    if (!glfwInit()) {
        std::cout << "Could not initialize glfw" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(this->getWidth(), this->getHeight(), this->title, NULL, NULL);

    if (!window) {
        std::cout << "Could not initialize window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, this->getWidth(), this->getHeight());
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void Window::start() {
    while (!glfwWindowShouldClose(this->window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int Window::getWidth() { return this->width; }

int Window::getHeight() { return this->height; }