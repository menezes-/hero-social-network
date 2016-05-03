#include "../include/Line.hpp"
#include "../include/utils.hpp"

Line::Line(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color, const glm::vec3 &color2, Shader *shader)
        : Drawable(pos, color,
                   shader, Type::LINE),
          pos2{pos2} {
    // posição no SRO (vec3) , cor (vec3)
    GLfloat vertices[] = {
            pos.x, pos.y, 0.0f, color.r, color.g, color.b,
            pos2.x, pos2.y, 0.0f, color2.r, color2.g, color2.b
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //habilita parametros de posição no SRO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    //habilita parametros de cor
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

Line::~Line() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

}

void Line::draw() {

    shader->enable();

    glBindVertexArray(VAO);
    //shader->setMatrix4fv("projection", glm::value_ptr(projection));
    //shader->setMatrix4fv("view", glm::value_ptr(view));
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);


}



