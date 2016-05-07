#include <stdexcept>
#include <iostream>
#include "../include/Graphics.hpp"

Graphics::Graphics(int width, int height) : width(width),
                                            height(height) {
    setup();
}

void Graphics::setup() {

    if (!glfwInit()) {
        throw std::runtime_error{"Nao foi possivel inicializar a biblioteca GLFW 3"};
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(width, height, "Marvel Social Network", nullptr, nullptr);

    if (window == nullptr) {
        std::string erro{"Nao foi possivel iniciar a janela!"};
        throw std::runtime_error{erro};
    }


    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        throw std::runtime_error{std::string{"Nao foi possivel inicializar o glew! "}};
    }

    //configua o viewport
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    //glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#ifndef NDEBUG
    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shader Language Version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif
}

GLFWwindow *Graphics::getWindow() const {
    return window;
}

int Graphics::getWidth() const {
    return width;
}

int Graphics::getHeight() const {
    return height;
}

Graphics::~Graphics() {
    glfwTerminate();
}


