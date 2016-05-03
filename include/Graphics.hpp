#pragma once
#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>

struct Character {
    GLuint     TextureID;  // Id da textura do OpenGL
    glm::ivec2 Size;       // tamanho do glyph
    glm::ivec2 Bearing;    // Deslocamento da linha de base para a esquerda / topo do glyph
    GLint     Advance;    // Deslocamento para avançar ao próximo glyph
};

class Graphics {
public:
    Graphics(int width, int height);

    SDL_Window *getWindow() const;

    int getWidth() const;

    int getHeight() const;

    const std::unordered_map<GLchar, Character> & getCharacters() const;

    Graphics() = default;

    Graphics(Graphics &&) = default;

    Graphics &operator=(Graphics &&) = default;


    virtual ~Graphics();


private:
    int width;
    int height;
    SDL_Window *window;
    SDL_GLContext glContext;

    std::string fontPath{"Calibri.ttf"};

    std::unordered_map<GLchar, Character> characters;

    void setupFontRendering();

    void setup();


};