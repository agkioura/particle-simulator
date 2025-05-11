#pragma once 

#include <glad/glad.h>

#include <fstream>
#include <string>

class Shader {
    public:
        unsigned int id;
        unsigned int vertexId;
        unsigned int fragmentId;

        Shader(const char* vertSrc, const char* fragSrc);
        std::string getSource(const char* shaderPath);
        void Use();
        void Delete();
    
    private:
        unsigned int compileShader(const char* source, GLenum type);
        void checkCompileErrors(unsigned int id, const std::string type);
        void checkLinkErrors(unsigned int program);
};