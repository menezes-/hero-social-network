#version 330 core
layout (location = 0) in vec4 position; // <vec2 pos, vec2 tex>
layout (location = 1) in vec3 textColor;

out vec2 TexCoords;
out vec3 charColor;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * vec4(position.xy, 0.0, 1.0);
    TexCoords = position.zw;
    charColor = textColor;
}