#pragma once


#include "Drawable.hpp"
#include "Graphics.hpp"
#include <unordered_map>

class Text final : public Drawable {

public:
    virtual void draw() override;

    Text(const glm::vec2 &pos, const glm::vec3 &color, Shader *shader,
         const std::string &text,
         const std::unordered_map<GLchar, Character> &char_map);

    virtual ~Text();

    Text(Text &&) = default;

    Text &operator=(Text &&) = default;


private:
    const std::unordered_map<GLchar, Character> &characters;
    const std::string txt;
    GLuint VBO, VAO;


};




