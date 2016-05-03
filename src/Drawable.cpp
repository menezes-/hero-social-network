#include "../include/Drawable.hpp"

glm::vec3 &Drawable::getPosition() {
    return position;
}

glm::vec3 &Drawable::getColor() {
    return color;
}

Drawable::Drawable(const glm::vec2 &pos, const glm::vec3 &color, Shader *shader, Type type) : position{pos.x, pos.y, 0.0f}, color{color},
                                                                                   shader{shader}, type{type} {

}


