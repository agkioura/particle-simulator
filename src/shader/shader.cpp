#include "../include/headers/shader/shader.h"

#include <iostream>
#include <vector>

Shader::Shader(const char* vertSrc, const char* fragSrc) {
    std::string vertexSrc = getSource(vertSrc);
    std::string fragmentSrc = getSource(fragSrc);

    const char* vertexSource = vertexSrc.c_str();
    const char* fragmentSource = fragmentSrc.c_str();
    
    vertexId = compileShader(vertexSource, GL_VERTEX_SHADER);
    fragmentId = compileShader(fragmentSource, GL_FRAGMENT_SHADER);
        
    id = glCreateProgram();
    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);
    
    glLinkProgram(id);
    checkLinkErrors(id);
    
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

unsigned int Shader::compileShader(const char* source, GLenum type) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    checkCompileErrors(id, type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
    return id;
}

void Shader::checkCompileErrors(unsigned int id, const std::string type) {
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        GLint logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> infoLog(logLength);
        glGetShaderInfoLog(result, logLength, nullptr, infoLog.data());
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                  << infoLog.data() << "\n";
        throw std::runtime_error("Shader compilation failed: " + type);
    }
}

void Shader::checkLinkErrors(unsigned int program) {
    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> infoLog(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, infoLog.data());
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n"
                  << infoLog.data() << "\n";
        throw std::runtime_error("Shader program linking failed");
    }
}

void Shader::Use() {
    glUseProgram(id);
}

void Shader::Delete() {
    glDeleteShader(id);
}

std::string Shader::getSource(const char* shaderPath) {
    std::ifstream input(shaderPath);

    std::string source;
    std::string buffer;
    while(getline(input, buffer)) {
        source.append(buffer);
        source.append("\n");
    }
    return source;
}