#include "../include/Triangle.hpp"
#include "../include/dbg.hpp"
#include <glm/gtx/string_cast.hpp>

Triangle::Triangle(const glm::vec2 &pos, const glm::vec3 &color, Shader *shader) : Drawable(pos, color,
                                                                                            shader, Type::TRIANGLE) {
    // posição no SRO (vec3) , cor (vec3)
    GLfloat vertices[] = {
            pos.x, pos.y+50, 0.0f, color.r, color.g, color.b,
            pos.x-50, pos.y-50, 0.0f, color.r, color.g, color.b,
            pos.x+50, pos.y-50, 0.0f, color.r, color.g, color.b
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

void Triangle::draw() {

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shader->enable();

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

}

Triangle::~Triangle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}