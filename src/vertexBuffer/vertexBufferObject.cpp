#include "../include/headers/vertexBuffer/vertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLfloat *vertices, GLsizeiptr size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBufferObject::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexBufferObject::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Destroy() {
    glDeleteBuffers(1, &id);
}