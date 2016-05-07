#pragma once

#include "Shader.hpp"
#include "Drawable.hpp"
#include "Graphics.hpp"
#include "Graph.hpp"
#include "FontAtlas.hpp"
#include <memory>
#include <vector>
#include <bitset>
#include <glm/glm.hpp>



enum Mode : short {
    RANDOM = 1,
    CIRCLE = 2,
    POPULAR = 3

};

struct TextVertice {
    GLfloat TextX; // posição na tela
    GLfloat TextY; // posição na tela
    GLfloat TextureX; // posição da textura
    GLfloat TextureY; // posição da textura
    //cores
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

using Triangle = std::array<GLfloat, 18>;
using Line = std::array<GLfloat, 12>;

template<class T, class A>
void fillPrimitiveBuff(GLuint &VAO, GLuint &VBO, const std::vector<T, A> &data);

class Scene {
private:
    std::unique_ptr<Shader> primitive;
    std::unique_ptr<Shader> text;
    const Graphics &graphics;
    const FontAtlas &fontAtlas;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront{0, 0, -3};
    glm::vec3 cameraUp{0, 1, 0};
    float cameraSpeed = 10.0f;

    glm::mat4 view;
    glm::mat4 projection;

    std::mt19937 mt;
    std::uniform_int_distribution<> dist_pos;
    std::uniform_int_distribution<> dist_color;

    std::vector<TextVertice> txtVertex;

    bool showLetters = false;

    float w, h;
    GLuint trigVAO, trigVBO, lineVAO, lineVBO, textVAO, textVBO;

    std::size_t trigVertexCount=0, lineVertexCount=0;

    glm::vec2 genPosition();

    glm::vec3 genColor();

    void updateViewMatrix();

    void updateProjectionMatrix();

    void fillTextBuff();

public:
    Scene(const Graphics &, const FontAtlas &);

    Scene(Scene &&) = default;

    Scene &operator=(Scene &&) = default;

    Triangle makeTriangle(const glm::vec2 &pos, const glm::vec3 &color);

    Line makeLine(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color,
                  const glm::vec3 &color2);

    void makeText(const glm::vec2 &pos, const glm::vec3 &color, const std::string &texto);

    void handleKeyboard();

    void zoom(float);

    void draw();

    void resetZoom();

    void fromGraph(const Graph &graph, Mode mode, int limit = 1000);

    virtual ~Scene();
};

