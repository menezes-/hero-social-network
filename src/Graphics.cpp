#include <stdexcept>

#include "../include/Graphics.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

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

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SDL_GL_SetSwapInterval(-1);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#ifndef NDEBUG
    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shader Language Version " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif

    glViewport(0, 0, width, height);

    setupFontRendering();

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

    for (auto &p: characters) {
        auto t = p.second.TextureID;
        glDeleteTextures(1, &t);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    SDL_Quit();

}

void Graphics::setupFontRendering() {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error{"ERROR::FREETYPE: Nao foi possivel iniciar a biblioteca Freetype"};
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        throw std::runtime_error{"ERROR::FREETYPE: Nao foi possivel carregar a fonte" + fontPath};
    }

    FT_Set_Pixel_Sizes(face, 0, 20);

    for (unsigned int c = 0; c < 256; ++c) { // tabela ascii extendida
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "WARNING::FREETYTPE: Nao foi possivel carregar  o glyph " << c << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        Character character{
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
        };

        characters.insert({c, character});

    }

}

const std::unordered_map<GLchar, Character> &Graphics::getCharacters() const {
    return characters;
}