#include <stdexcept>
#include <iostream>
#include "../include/Graphics.hpp"

Graphics::Graphics(int width, int height) : width(width),
                                            height(height) {
    setup();
}

void Graphics::setup() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        throw std::runtime_error{"Nao foi possivel inicializar a biblioteca SDL2"};
    }


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);


    window = SDL_CreateWindow("Marvel Social Network", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);

    if (!window) {
        std::string erro{"Nao foi possivel iniciar a janela! " + std::string{SDL_GetError()}};
        throw std::runtime_error{erro};
    }


    glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);


    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        throw std::runtime_error{std::string{"Nao foi possivel inicializar o glew! "}};
    }

    //glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_GL_SetSwapInterval(-1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#ifndef NDEBUG
    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shader Language Version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif

    glViewport(0, 0, width, height);


}

SDL_Window *Graphics::getWindow() const {
    return window;
}

int Graphics::getWidth() const {
    return width;
}

int Graphics::getHeight() const {
    return height;
}

Graphics::~Graphics() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

}


