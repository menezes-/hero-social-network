#include "../include/Scene.hpp"
#include "../include/utils.hpp"
#include <GLFW/glfw3.h>
#include <chrono>

template<class T, class A>
void fillPrimitiveBuff(GLuint &VAO, GLuint &VBO, const std::vector<T, A> &data) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), &data[0], GL_STATIC_DRAW);

    //habilita parametros de posição no SRO
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) 0);

    //habilita parametros de cor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *) (3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Triangle makeTriangle(const glm::vec2 &pos, const glm::vec3 &color) {

    return Triangle {
            pos.x, pos.y + 200, 0.0f, color.r, color.g, color.b,
            pos.x - 200, pos.y - 200, 0.0f, color.r, color.g, color.b,
            pos.x + 200, pos.y - 200, 0.0f, color.r, color.g, color.b
    };
}

Line makeLine(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color,
              const glm::vec3 &color2) {

    return Line {
            pos.x, pos.y, 0.0f, color.r, color.g, color.b,
            pos2.x, pos2.y, 0.0f, color2.r, color2.g, color2.b
    };
}

Scene::Scene(int width, int height, const FontAtlas &fontAtlas, const Config &config)
        : fontAtlas{fontAtlas}, config{config}, projection{
        glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height))}, oWidth{width}, oHeight{height} {

    mt = radomNumberGenerator();
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt.seed(seed);
    dist_pos = std::uniform_int_distribution<>(-100000, 100000);
    dist_color = std::uniform_int_distribution<>(0, 255);

    primitive = make_unique<Shader>("shaders\\primitive.vs.glsl", "shaders\\primitive.fs.glsl");
    text = make_unique<Shader>("shaders\\text.vs.glsl", "shaders\\text.fs.glsl");
    text->setUniform1i("text", 0);

    windowWidth = oWidth;
    windowHeight = oHeight;

    cameraPos = glm::vec3{windowWidth / 2, windowHeight / 2, 0};
    updateProjectionMatrix();
    updateViewMatrix();
    adjustCameraSpeed();
}


void Scene::draw() {

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    primitive->enable();

    glBindVertexArray(trigVAO);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(trigVertexCount));
    glBindVertexArray(0);


    glBindVertexArray(lineVAO);
    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(lineVertexCount));
    glBindVertexArray(0);

    if (showLetters) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        text->enable();
        glBindVertexArray(textVAO);
        glBindTexture(GL_TEXTURE_2D, fontAtlas.getTexture());
        auto size = static_cast<GLsizei>(textVertexCount); //cada quad tem 6 vertices
        glDrawArrays(GL_TRIANGLES, 0, size);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

void Scene::processInput(double dt) {
    float deltaTime = static_cast<float>(dt);

    if (Keys[GLFW_KEY_D]) {
        moveCamera(CameraDirection::RIGHT, deltaTime);
    }
    if (Keys[GLFW_KEY_A]) {
        moveCamera(CameraDirection::LEFT, deltaTime);
    }
    if (Keys[GLFW_KEY_W]) {
        moveCamera(CameraDirection::UP, deltaTime);
    }
    if (Keys[GLFW_KEY_S]) {
        moveCamera(CameraDirection::DOWN, deltaTime);
    }
    if (Keys[GLFW_KEY_E]) {
        zoom(0.8f);
    }
    if (Keys[GLFW_KEY_Q]) {
        zoom(1.2f);
    }
    if (Keys[GLFW_KEY_R]) {
        resetCamera();
    }
    if (Keys[GLFW_KEY_L]) {
        showLetters = false;
    }
    if (Keys[GLFW_KEY_K]) {
        showLetters = true;
    }

}

void Scene::zoom(float scale) {

    windowWidth *= scale;
    windowHeight *= scale;
    projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);

    adjustCameraSpeed();
    updateProjectionMatrix();
}

void Scene::resetZoom() {

    windowWidth = oWidth / 2.0f;
    windowHeight = oHeight / 2.0f;

    projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);

    adjustCameraSpeed();
    updateProjectionMatrix();

}

void Scene::resetCamera() {
    cameraPos = glm::vec3{oWidth / 2, oHeight / 2, 0};
    cameraFront = glm::vec3{0, 0, -3};
    cameraUp = glm::vec3{0, 1, 0};

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    updateViewMatrix();
    adjustCameraSpeed();

}

void Scene::moveCamera(CameraDirection direction, float deltaTime) {
    auto speed = cameraSpeed * deltaTime;

    switch (direction) {

        case UP:
            cameraPos += glm::vec3(0, 1, 0) * speed;
            break;
        case DOWN:
            cameraPos -= glm::vec3(0, 1, 0) * speed;
            break;
        case LEFT:
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
            break;
        case RIGHT:
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
            break;
    }
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    updateViewMatrix();

}

glm::vec2 Scene::genPosition() {
    return glm::vec2{dist_pos(mt), dist_pos(mt)};
}

glm::vec3 Scene::genColor() {
    int red = dist_color(mt);
    int green = dist_color(mt);
    int blue = dist_color(mt);

    return glm::vec3{red / 255.0f, blue / 255.0f, green / 255.0f};
}

void Scene::fromGraph(const Graph &graph, Mode mode, int limit) {
    auto colors = std::unordered_map<std::string, glm::vec3>();
    auto positions = std::unordered_map<std::string, glm::vec2>();
    auto t_drawed = std::vector<bool>(graph.vertices_size, false);
    auto triangles = std::vector<Triangle>{};
    auto lines = std::vector<Line>{};
    auto texts = std::vector<TextVertice>{};
    int e_counter = 0;
    std::size_t c = 0;
    auto centerX = oWidth / 2;
    auto centerY = oHeight / 2;
    auto getPos = [&](const std::string &name, std::size_t id) {


        auto search = positions.find(name);
        glm::vec2 pos;
        if (search == positions.end()) {

            if (mode == Mode::POPULAR || mode == Mode::CIRCLE) {
                auto appe = graph.appearances[id];
                auto radius_ex = (mode == Mode::POPULAR) ? (appe / 500.0f) * 10000 : dist_pos(mt);
                float x, y;
                if (c == 0) {
                    x = centerX;
                    y = centerY;
                } else {
                    auto angle = ((static_cast<float>(c)) / graph.vertices_size) * 360.0f;
                    x = this->dist_color(this->mt) + (centerX) + (std::sin(angle) * (radius_ex));

                    y = this->dist_color(this->mt) + (centerY) + (std::cos(angle) * (radius_ex));

                }
                pos = glm::vec2{x, y};

                c += 50;
            } else {
                pos = genPosition();
            }

            positions.insert({name, pos});
        } else {
            pos = search->second;
        }
        return pos;
    };

    auto getColor = [&colors, this](const std::string &name) {
        auto search = colors.find(name);
        glm::vec3 pos;
        if (search == colors.end()) {
            pos = this->genColor();
            colors.insert({name, pos});
        } else {
            pos = search->second;
        }

        return pos;
    };

    for (std::size_t i = 0; i < graph.vertices_size; ++i) {
        for (std::size_t j = 0; j < graph.vertices_size; ++j) {
            if (graph.matrix[graph.getArrPos(i, j)]) {

                auto name1 = graph.getName(i);
                auto pos1 = getPos(name1, i);
                auto color1 = getColor(name1);
                if (!t_drawed[i]) {
                    triangles.emplace_back(makeTriangle(pos1, color1));
                    fontAtlas.makeText(texts, pos1, color1, name1);
                }

                auto name2 = graph.getName(j);
                auto pos2 = getPos(name2, j);
                auto color2 = getColor(name2);
                if (!t_drawed[j]) {
                    triangles.emplace_back(makeTriangle(pos2, color2));
                    fontAtlas.makeText(texts, pos2, color2, name2);
                }
                lines.emplace_back(makeLine(pos1, pos2, color2, color1));


                if (e_counter > limit) {
                    goto fim;
                }
                e_counter++;

            }

        }

    }
    fim:
    fillPrimitiveBuff(lineVAO, lineVBO, lines);
    fillPrimitiveBuff(trigVAO, trigVBO, triangles);

    trigVertexCount = triangles.size() * 3; // numero de vertices: total de triangules * 3 (tres vertices por triangulo)
    lineVertexCount = lines.size() * 2; // 2 vertices por linha, numero_de_linhas*2
    textVertexCount = texts.size() * 6; // 6 vertices, 3 triangulos, 1 quad para a textura
    fillTextBuff(texts);

}

void Scene::fillTextBuff(const std::vector<TextVertice> txtVertex) {

    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);

    glBindBuffer(GL_ARRAY_BUFFER, textVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(TextVertice) * txtVertex.size(), &txtVertex[0], GL_STATIC_DRAW);

    // posição e posição da textura
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);

    //cor
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *) (4 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

void Scene::updateViewMatrix() {

    primitive->enable();
    primitive->setMatrix4fv("view", glm::value_ptr(view));

    text->enable();
    text->setMatrix4fv("view", glm::value_ptr(view));


}

void Scene::updateProjectionMatrix() {

    primitive->enable();
    primitive->setMatrix4fv("projection", glm::value_ptr(projection));

    text->enable();
    text->setMatrix4fv("projection", glm::value_ptr(projection));

}

Scene::~Scene() {

    GLuint vaos[] = {trigVAO, lineVAO, textVAO};
    GLuint vbos[] = {trigVBO, lineVBO, textVBO};

    glDeleteVertexArrays(3, vaos);
    glDeleteBuffers(3, vbos);

}

void Scene::adjustCameraSpeed() {
    cameraSpeed = glm::vec3{windowWidth * 2, windowHeight * 2, 1};
}

