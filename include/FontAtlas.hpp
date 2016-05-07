#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <array>

constexpr int ASCII_START = 32;
constexpr int ASCII_END = 128;
constexpr unsigned int MAX_TEXTURE_WIDTH = 1024;


struct CharacterInfo {
    glm::vec2 Size;       // tamanho do glyph
    glm::vec2 Bearing;    // Deslocamento da linha de base para a esquerda / topo do glyph
    glm::vec2 Advance;    // Deslocamento para avançar ao próximo glyph
    GLfloat OffsetX; // Deslocamento do x em coordenadas da textura
    GLfloat OffsetY; // Deslocamento do Y em coordenadas da textura

};
using CharacterContainer = std::array<CharacterInfo, ASCII_END>;

class FontAtlas {
private:
    unsigned int fontSize;
    std::string fontPath;

    GLuint texture;

    CharacterContainer ci;

    unsigned int atlas_width = 0;
    unsigned int atlas_height = 0;

    void setupAtlas();

public:
    GLuint getTexture() const;

    const CharacterContainer &getCi() const;

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    FontAtlas(unsigned int fontSize, const std::string &fontPath);

    FontAtlas(FontAtlas &&) = default;

    FontAtlas &operator=(FontAtlas &&) = default;

    virtual ~FontAtlas();
};