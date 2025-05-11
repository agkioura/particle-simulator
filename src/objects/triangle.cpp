#include "../include/headers/objects/triangle.h"

Triangle::Triangle(float *data) {
    this->vertices = data;
}

void Triangle::render(VertexArrayObject vao, Shader shader) {
    shader.Use();
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}