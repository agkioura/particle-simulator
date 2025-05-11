#pragma once

#include <glad/glad.h>
#include "../vertexBuffer/vertexBufferObject.h"

class VertexArrayObject {
    public:
        unsigned int id;
        VertexArrayObject();

        void LinkAttrib(VertexBufferObject& VBO, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();
};