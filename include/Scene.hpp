#pragma once

#include "Shader.hpp"
#include "Drawable.hpp"
#include "Graph.hpp"
#include "FontAtlas.hpp"
#include "Config.hpp"
#include <memory>
#include <vector>
#include <bitset>
#include <glm/glm.hpp>

constexpr GLfloat PI = 3.141592;

enum Mode : short {
    RANDOM = 1,
    CIRCLE = 2,
    POPULAR = 3

};

enum CameraDirection : short {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct CircleVertice {
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

using Triangle = std::array<GLfloat, 18>;
using Line = std::array<GLfloat, 12>;

template<class T, class A>
void fillPrimitiveBuff(GLuint &VAO, GLuint &VBO, const std::vector<T, A> &data);

Triangle makeTriangle(const glm::vec2 &pos, const glm::vec3 &color);

Line makeLine(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color,
              const glm::vec3 &color2);

void makeCircle(std::vector<CircleVertice> &vertex, const glm::vec2 &center, const glm::vec3 &color, int fragments);

class Scene {
private:
    std::unique_ptr<Shader> primitive;
    std::unique_ptr<Shader> text;
    const FontAtlas &fontAtlas;
    const Config &config;

    glm::vec3 cameraPos;
    glm::vec3 cameraFront{0, 0, -3};
    glm::vec3 cameraUp{0, 1, 0};
    glm::vec3 cameraSpeed;

    glm::mat4 view;
    glm::mat4 projection;

    std::mt19937 mt;
    std::uniform_int_distribution<> dist_pos;
    std::uniform_int_distribution<> dist_color;

    bool showLetters = false;

    int oWidth, oHeight; // tamanho da window original
    GLfloat windowWidth, windowHeight;

    GLuint trigVAO, trigVBO, lineVAO, lineVBO, textVAO, textVBO, circleVAO, circleVBO;

    std::size_t circleVertexCount = 0, trigVertexCount = 0, lineVertexCount = 0, textVertexCount = 0;

    glm::vec2 genPosition();

    glm::vec3 genColor();

    void updateViewMatrix();

    void updateProjectionMatrix();

    void adjustCameraSpeed();

    void fillTextBuff(const std::vector<TextVertice> txtVertex);

public:
    Scene(int width, int height, const FontAtlas &, const Config &);

    Scene(Scene &&) = default;

    Scene &operator=(Scene &&) = default;

    void moveCamera(CameraDirection direction, float deltaTime);

    void zoom(float);

    void draw();

    void resetZoom();

    void resetCamera();

    void fromGraph(const Graph &graph, Mode mode);

    void processInput(double deltaTime);

    std::bitset<1024> Keys{false};

    virtual ~Scene();
};

