#pragma once

#include "Drawable.hpp"


class Triangle final : public Drawable {
private:

    GLuint VBO, VAO;


public:
    virtual void draw() override;

    Triangle(const glm::vec2 &pos, const glm::vec3 &color, Shader *shader);

    Triangle(Triangle &&) = default;

    Triangle &operator=(Triangle &&) = default;

    virtual ~Triangle();
};
