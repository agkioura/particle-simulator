#include "../include/headers/window/window.h"
#include "../include/headers/vertexBuffer/vertexBufferObject.h"
#include "../include/headers/vertexArray/vertexArrayObject.h"
#include "../include/headers/shader/shader.h"

#include "../include/headers/objects/triangle.h"

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
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, this->getWidth(), this->getHeight());
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void Window::start() {
    GLfloat data[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
    };
    
    Triangle t(data);

    VertexBufferObject vbo(data, sizeof(data));
    VertexArrayObject vao;
    vao.Bind();
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    Shader shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    while (!glfwWindowShouldClose(this->window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        t.render(vao, shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int Window::getWidth() { return this->width; }

int Window::getHeight() { return this->height; }