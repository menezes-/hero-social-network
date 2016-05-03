#include "../include/Text.hpp"

Text::Text(const glm::vec2 &pos, const glm::vec3 &color, Shader *shader,
           const std::string &text,
           const std::unordered_map<GLchar, Character> &char_map) : Drawable(pos, color, shader, Type::TEXT), characters{char_map},
                                                                    txt{text} {

    /*
     * como vamos gerar os quads conforme as texturas, apenas alocamos a
     * memória para o VBO. o VBO é do tipo GL_DYNAMIC_DRAW pois será atualizado
     * com as texturas
     */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //shader->enable();



}

void Text::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glActiveTexture(GL_TEXTURE0);

    shader->enable();
    shader->setUniform3f("textColor", color);

    glBindVertexArray(VAO);
    auto x =  position.x;
    auto y =  position.y;


    for (const auto &c: txt) {

        Character ch;

        auto search = characters.find(c);

        if (search != characters.end()) {
            ch = search->second;
        } else {
            // não achei o caracter no mapa então coloca '?'
            ch = characters.at('?');
        }

        GLfloat ypos = y + ch.Bearing.y;
        GLfloat xpos = x + ch.Bearing.x;

        GLfloat w = ch.Size.x ;
        GLfloat h = ch.Size.y ;

        // Atualiza o VBO para cada caracter
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // vai para o próximo glyph
        x += (ch.Advance >> 6); // 2^6 = 64, valor em pixel

    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

Text::~Text() {

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

}