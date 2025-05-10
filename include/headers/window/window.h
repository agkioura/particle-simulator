#pragma once   

#include <Glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow *window;
        int width, height;
        const char* title;

    public:
        Window(int width, int height, const char* title);
        ~Window();

        int createContext();
        void start();

        int getWidth();
        int getHeight();
};