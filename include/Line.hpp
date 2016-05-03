#pragma once

#include "Drawable.hpp"

class Line final : public Drawable {

public:
    Line(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color, const glm::vec3 &color2, Shader *shader);

    virtual void draw() override;

    Line(Line &&) = default;

    Line &operator=(Line &&) = default;

    virtual ~Line();

private:
    GLuint VBO, VAO;
    glm::vec2 pos2;


};


