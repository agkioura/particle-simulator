#pragma once 

#include <glad/glad.h>

#include "../vertexBuffer/vertexBufferObject.h"
#include "../vertexArray/vertexArrayObject.h"
#include "../shader/shader.h"

class Triangle {
    private:
        float *vertices;

    public:
        Triangle(float *data);

        void render(VertexArrayObject vao, Shader shader);
};