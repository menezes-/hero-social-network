#pragma once

#include <unordered_map>
#include "Graphics.hpp"


class Shader {

private:
    GLuint program;

    std::string readFile(const char *filename);

    GLuint createShader(GLenum type, const std::string &code);


public:
    Shader(const char *vertexPath, const char *fragmentPath);

    void enable();

    void disable();

    void setMatrix4fv(const char* uniform_name, const GLfloat *value);
    void setUniform3f(const char* uniform_name, const glm::vec3&);


    GLuint getProgram() const {
        return program;
    }
};
