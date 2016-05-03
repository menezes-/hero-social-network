#pragma once

#include "Shader.hpp"
#include "Drawable.hpp"
#include "Graphics.hpp"
#include "Graph.hpp"
#include <memory>
#include <vector>
#include <bitset>
#include <glm/glm.hpp>

enum Mode : short {
    RANDOM = 1,
    CIRCLE = 2,
    POPULAR = 3

};

class Scene {
private:
    std::vector<std::unique_ptr<Drawable>> objects;
    std::unique_ptr<Shader> triangle;
    std::unique_ptr<Shader> text;
    std::unique_ptr<Shader> line;
    const Graphics &graphics;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront{0, 0, -3};
    glm::vec3 cameraUp{0, 1, 0};
    float cameraSpeed = 10.0f;

    glm::mat4 view;
    glm::mat4 projection;

    std::mt19937 mt;
    std::uniform_int_distribution<> dist_pos;
    std::uniform_int_distribution<> dist_color;

    glm::vec2 genPosition();

    glm::vec3 genColor();

    void updateViewMatrix();

    void updateProjectionMatrix();

    bool showLetters = false;

    float w, h;

public:
    Scene(const Graphics &);

    void addTriangle(const glm::vec2 &pos, const glm::vec3 &color, const std::string &);

    void addLine(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color, const glm::vec3 &color2);

    void handleKeyboard();

    void zoom(float);

    void draw();

    void resetZoom();

    void fromGraph(const Graph &graph, Mode mode, int limit = 1000);

};

