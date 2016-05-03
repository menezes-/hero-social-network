#include "../include/Scene.hpp"
#include "../include/utils.hpp"
#include "../include/Triangle.hpp"
#include "../include/Text.hpp"
#include "../include/Line.hpp"
#include <cmath>
#include <iostream>


Scene::Scene(const Graphics &graphics)
        : objects{}, graphics{graphics}, projection{
        glm::ortho(0.0f, static_cast<float>(graphics.getWidth()), 0.0f, static_cast<float>(graphics.getHeight()))} {

    mt = radomNumberGenerator();
    dist_pos = std::uniform_int_distribution<>(-10000, 10000);
    dist_color = std::uniform_int_distribution<>(0, 255);

    triangle = make_unique<Shader>("shaders\\trig.vs.glsl", "shaders\\trig.fs.glsl");
    text = make_unique<Shader>("shaders\\text.vs.glsl", "shaders\\text.fs.glsl");
    line = make_unique<Shader>("shaders\\line.vs.glsl", "shaders\\line.fs.glsl");
    w = graphics.getWidth();
    h = graphics.getHeight();

    cameraPos = glm::vec3{w / 2, h / 2, 0};

    updateProjectionMatrix();
    updateViewMatrix();


}

void Scene::draw() {

    for (const auto &obj: objects) {
        if (obj->type != Type::TEXT) {
            obj->draw();
        } else {
            if (showLetters) {
                obj->draw();
            }
        }

    }

}

void Scene::addTriangle(const glm::vec2 &pos, const glm::vec3 &color, const std::string &txt) {
    objects.emplace_back(
            make_unique<Text>(pos, color, text.get(),
                              txt,
                              graphics.getCharacters()));

    objects.emplace_back(make_unique<Triangle>(pos, color, triangle.get()));
}


void Scene::addLine(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color, const glm::vec3 &color2) {

    objects.emplace_back(make_unique<Line>(pos, pos2, color, color2, line.get()));
}

void Scene::handleKeyboard() {

    static float deltaTime = 0.0f;
    static float lastFrame = 0.0f;

    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const auto *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_R]) { //reseta a posição da camera
        cameraPos = glm::vec3{1, 1, 0};
        cameraFront = glm::vec3{0, 0, -3};
        cameraUp = glm::vec3{0, 1, 0};

    }


    float speed = cameraSpeed * deltaTime;

    if (keys[SDL_SCANCODE_W]) {
        cameraPos += speed * glm::vec3(0, 1, 0);
    }

    if (keys[SDL_SCANCODE_S]) {
        cameraPos -= speed * glm::vec3(0, 1, 0);
    }

    if (keys[SDL_SCANCODE_A]) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if (keys[SDL_SCANCODE_D]) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }

    if (keys[SDL_SCANCODE_E]) {
        zoom(0.8f);
    }

    if (keys[SDL_SCANCODE_Q]) {
        zoom(1.2f);
    }

    if (keys[SDL_SCANCODE_L]) {
        showLetters = false;
    }
    if (keys[SDL_SCANCODE_K]) {
        showLetters = true;
    }


    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    updateViewMatrix();


}

void Scene::zoom(float scale) {

    w *= scale;
    h *= scale;
    projection = glm::ortho(0.0f, w, 0.0f, h);

    updateProjectionMatrix();
}

void Scene::resetZoom() {

    w = graphics.getWidth()/2;
    h = graphics.getHeight()/2;

    projection = glm::ortho(0.0f, w, 0.0f, h);

    updateProjectionMatrix();

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

    int e_counter = 0;

    std::size_t c = 0;
    //auto radius = 500.0f;
    //auto base_radius = 1000.0f;
    auto centerX = graphics.getWidth() / 2;
    auto centerY = graphics.getHeight() / 2;
    auto getPos = [&](const std::string &name, std::size_t id) {


        auto search = positions.find(name);
        glm::vec2 pos;
        if (search == positions.end()) {

            if (mode == Mode::POPULAR || mode == Mode::CIRCLE) {
                auto appe = graph.appearances[id];
                auto radius_ex = (mode == Mode::POPULAR) ? (appe / 500.0f) * 1000 : 5000.0f;
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

                    addTriangle(pos1, color1, name1);
                }

                auto name2 = graph.getName(j);
                auto pos2 = getPos(name2, j);
                auto color2 = getColor(name2);
                if (!t_drawed[j]) {

                    addTriangle(pos2, color2, name2);
                }
                addLine(pos1, pos2, color2, color1);
                if (e_counter > limit) {
                    return;
                }
                e_counter++;

            }

        }

    }


}


void Scene::updateViewMatrix() {

    triangle->enable();
    triangle->setMatrix4fv("view", glm::value_ptr(view));

    line->enable();
    line->setMatrix4fv("view", glm::value_ptr(view));

    text->enable();
    text->setMatrix4fv("view", glm::value_ptr(view));


}

void Scene::updateProjectionMatrix() {

    triangle->enable();
    triangle->setMatrix4fv("projection", glm::value_ptr(projection));

    line->enable();
    line->setMatrix4fv("projection", glm::value_ptr(projection));

    text->enable();
    text->setMatrix4fv("projection", glm::value_ptr(projection));

}


