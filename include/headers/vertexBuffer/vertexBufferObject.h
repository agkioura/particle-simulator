#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBufferObject {
    public:
        unsigned int id;
        VertexBufferObject(GLfloat *vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Destroy();
};