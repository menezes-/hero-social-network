#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../include/FontAtlas.hpp"

FontAtlas::FontAtlas(unsigned int fontSize, const std::string &fontPath) : fontSize(fontSize), fontPath(fontPath) {
    setupAtlas();
}

void FontAtlas::setupAtlas() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error{"ERROR::FREETYPE: Nao foi possivel iniciar a biblioteca Freetype"};
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        throw std::runtime_error{"ERROR::FREETYPE: Nao foi possivel carregar a fonte" + fontPath};
    }


    FT_Set_Pixel_Sizes(face, 0, fontSize);

    FT_GlyphSlot g = face->glyph; // atalho, a cada chamada de FT_Load_Char face->glyph é atualizado

    /**
     * OpenGL tem um limite de tamanho para as dimensões de textura, teoricamente esse valor estaria
     * em GL_MAX_TEXTURE_SIZE porém, aparentemente, esse valor não é muito confiável. Então o valor esta definido
     * na constante MAX_TEXTURE_WIDTH quando esse valor é atingido nos mudaos para a próxima linha da textura.
     *
     *
     * como referencia ver: https://www.freetype.org/freetype2/docs/glyphs/glyphs-3.html
     */

    unsigned int row_width = 0;
    unsigned int row_height = 0;

    //nsigned long para compatibilidade com o parametro de FT_Load_char
    for (unsigned long i = ASCII_START; i < ASCII_END; ++i) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::cerr << "WARNING::FREETYTPE: Nao foi possivel carregar  o glyph " << i << std::endl;
            continue;
        }
        auto bw = g->bitmap.width;
        auto bh = g->bitmap.rows;

        if (row_width + bw >= MAX_TEXTURE_WIDTH) {
            atlas_width = std::max(atlas_width, row_width);
            atlas_height += row_height;
            row_width = 0;
            row_height = 0;
        }
        row_width += bw;
        row_height = std::max(bh, row_height);
    }

    //Caso não tenha caido no if do for acima
    atlas_width = std::max(atlas_width, row_width);
    atlas_height += row_height;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlas_width, atlas_height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    /**
     * preenche a textura com os glifos e grava as informações dos glifos
     */
    int offset_x = 0;
    int offset_y = 0;
    row_height = 0;
    for (unsigned long i = ASCII_START; i < ASCII_END; ++i) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            continue;
        }

        if (offset_x + g->bitmap.width >= MAX_TEXTURE_WIDTH) { //muda a linha
            offset_y += row_height;
            row_height = 0;
            offset_x = 0;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, offset_x, offset_y, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE,
                        g->bitmap.buffer);

        ci[i].Size = glm::vec2{g->bitmap.width, g->bitmap.rows};
        ci[i].Bearing = glm::vec2{g->bitmap_left, g->bitmap_top};
        ci[i].Advance = glm::vec2{g->advance.x >> 6, g->advance.y >> 6}; // 2^6 = 64, valor em pixel
        // coordenadas de textura vao de (0,0) a (1,1) por isso divide pelo tamanho total para normalizar as coordenadas
        ci[i].OffsetX = offset_x / static_cast<GLfloat>(atlas_width);
        ci[i].OffsetY = offset_y / static_cast<GLfloat>(atlas_height);

        row_height = std::max(row_height, g->bitmap.rows);
        offset_x += g->bitmap.width;

    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glBindTexture(GL_TEXTURE_2D, 0);

}

GLuint FontAtlas::getTexture() const {
    return texture;
}

const CharacterContainer &FontAtlas::getCi() const {
    return ci;
}

unsigned int FontAtlas::getWidth() const {
    return atlas_width;
}

unsigned int FontAtlas::getHeight() const {
    return atlas_height;
}


FontAtlas::~FontAtlas() {
    glDeleteTextures(1, &texture);
}