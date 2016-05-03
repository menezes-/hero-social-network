#include "../include/Shader.hpp"
#include <fstream>
#include <vector>
#include <iostream>

std::string Shader::readFile(const char *filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in) {
        return (std::string{(std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()});
    }
    throw (errno);
}

Shader::Shader(const char *vertexPath, const char *fragmentPath) {

    auto vertexShader = createShader(GL_VERTEX_SHADER, readFile(vertexPath));
    auto fragmentShader = createShader(GL_FRAGMENT_SHADER, readFile(fragmentPath));

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetShaderiv(program, GL_LINK_STATUS, &success);

    if (success == GL_FALSE) {

        GLint info_log_length;
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

        std::vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(program, info_log_length, NULL, &shader_log[0]);
        throw std::runtime_error{std::string{std::string{"ERROR linkando o shader: "} + std::string{&shader_log[0]}}};

    }


}

GLuint Shader::createShader(GLenum type, const std::string &code) {

    const GLchar *code_ptr = code.c_str();

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &code_ptr, nullptr);
    glCompileShader(id);

    GLint success;

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE) {
        GLint info_log_length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);

        std::vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(id, info_log_length, nullptr, &shader_log[0]);

        throw std::runtime_error{std::string{"ERROR Compilando shader: "} + std::string{&shader_log[0]}};

    }

    return id;
}

void Shader::enable() {

    glUseProgram(program);

}

void Shader::disable() {

    glUseProgram(0);

}

void Shader::setMatrix4fv(const char *uniform_name, const GLfloat *value) {

    glUniformMatrix4fv(glGetUniformLocation(program, uniform_name), 1, GL_FALSE, value);

}

void Shader::setUniform3f(const char *uniform_name, const glm::vec3 &vec3) {

    glUniform3f(glGetUniformLocation(program, uniform_name), vec3.x, vec3.y, vec3.z);

}






