#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"

enum Type: short{
    TRIANGLE,
    LINE,
    TEXT
};

class Drawable {
protected:
    glm::vec3 position;
    glm::vec3 color;
    Shader* shader;

public:
    Drawable(const glm::vec2 &pos, const glm::vec3 &color, Shader *shader, Type type);

    glm::vec3 &getPosition();

    glm::vec3 &getColor();

    const Type type;

    virtual void draw() = 0;

    virtual ~Drawable() = default;
};
