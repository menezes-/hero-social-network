#include "../include/Scene.hpp"
#include "../include/utils.hpp"

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

Scene::Scene(const Graphics &graphics, const FontAtlas &fontAtlas)
        : graphics{graphics}, fontAtlas{fontAtlas}, projection{
        glm::ortho(0.0f, static_cast<float>(graphics.getWidth()), 0.0f, static_cast<float>(graphics.getHeight()))} {

    mt = radomNumberGenerator();
    dist_pos = std::uniform_int_distribution<>(-10000, 10000);
    dist_color = std::uniform_int_distribution<>(0, 255);

    primitive = make_unique<Shader>("shaders\\primitive.vs.glsl", "shaders\\primitive.fs.glsl");
    text = make_unique<Shader>("shaders\\text.vs.glsl", "shaders\\text.fs.glsl");
    text->setUniform1i("text", 0);

    w = graphics.getWidth();
    h = graphics.getHeight();

    txtVertex = std::vector<TextVertice>{};

    cameraPos = glm::vec3{w / 2, h / 2, 0};
    updateProjectionMatrix();
    updateViewMatrix();
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
        auto size = static_cast<GLsizei>(txtVertex.size()) * 6; //cada quad tem 6 vertices
        glDrawArrays(GL_TRIANGLES, 0, size);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

Triangle Scene::makeTriangle(const glm::vec2 &pos, const glm::vec3 &color) {

    return Triangle {
            pos.x, pos.y + 50, 0.0f, color.r, color.g, color.b,
            pos.x - 50, pos.y - 50, 0.0f, color.r, color.g, color.b,
            pos.x + 50, pos.y - 50, 0.0f, color.r, color.g, color.b
    };
}


Line Scene::makeLine(const glm::vec2 &pos, const glm::vec2 &pos2, const glm::vec3 &color,
                     const glm::vec3 &color2) {

    return Line {
            pos.x, pos.y, 0.0f, color.r, color.g, color.b,
            pos2.x, pos2.y, 0.0f, color2.r, color2.g, color2.b
    };
}

void Scene::makeText(const glm::vec2 &pos, const glm::vec3 &color, const std::string &texto) {


    auto x = pos.x;
    auto y = pos.y;
    auto ci = fontAtlas.getCi();
    auto atlas_width = fontAtlas.getWidth();
    auto atlas_height = fontAtlas.getHeight();

    for (const auto &ch: texto) {
        auto info = ci[ch];

        GLfloat xpos = x + info.Bearing.x;
        GLfloat ypos = -y - info.Bearing.y;

        //vai pra próxima posição
        x += info.Advance.x;
        y += info.Advance.y;

        if (!w || !h) { // caracteres que não tem tamanho são pulados, tipo espaço
            continue;
        }

        GLfloat w = info.Size.x;
        GLfloat h = info.Size.y;

        GLfloat offsetx = info.OffsetX;

        txtVertex.emplace_back(TextVertice{xpos, -ypos, offsetx, 0, color.r, color.g, color.b});

        txtVertex.emplace_back(
                TextVertice{xpos + w, -ypos, offsetx + w / atlas_width, 0, color.r, color.g, color.b});
        txtVertex.emplace_back(
                TextVertice{xpos, -ypos - h, offsetx, h / atlas_height, color.r, color.g, color.b});
        txtVertex.emplace_back(
                TextVertice{xpos + w, -ypos, offsetx + w / atlas_width, 0, color.r, color.g, color.b});
        txtVertex.emplace_back(
                TextVertice{xpos, -ypos - h, offsetx, h / atlas_height, color.r, color.g, color.b});
        txtVertex.emplace_back(
                TextVertice{xpos + w, -ypos - h, offsetx + w / atlas_width, h / atlas_height, color.r,
                            color.g, color.b});

    }
}


void Scene::handleKeyboard() {

    static float deltaTime = 0.0f;
    static float lastFrame = 0.0f;

    float currentFrame = SDL_GetTicks();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const auto *keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_R]) { //reseta a posição da camera
        cameraPos = glm::vec3{graphics.getWidth() / 2, graphics.getHeight() / 2, 0};
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

    w = graphics.getWidth() / 2;
    h = graphics.getHeight() / 2;

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
    auto triangles = std::vector<Triangle>{};
    auto lines = std::vector<Line>{};
    int e_counter = 0;
    std::size_t c = 0;
    auto centerX = graphics.getWidth() / 2;
    auto centerY = graphics.getHeight() / 2;
    auto getPos = [&](const std::string &name, std::size_t id) {


        auto search = positions.find(name);
        glm::vec2 pos;
        if (search == positions.end()) {

            if (mode == Mode::POPULAR || mode == Mode::CIRCLE) {
                auto appe = graph.appearances[id];
                auto radius_ex = (mode == Mode::POPULAR) ? (appe / 500.0f) * 5000 : 10000.0f;
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
                    makeText(pos1, color1, name1);
                }

                auto name2 = graph.getName(j);
                auto pos2 = getPos(name2, j);
                auto color2 = getColor(name2);
                if (!t_drawed[j]) {
                    triangles.emplace_back(makeTriangle(pos2, color2));
                    makeText(pos2, color2, name2);
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
    fillPrimitiveBuff(trigVAO, trigVBO, triangles);
    fillPrimitiveBuff(lineVAO, lineVBO, lines);

    trigVertexCount = triangles.size() * 3; // numero de vertices: total de triangules * 3 (tres vertices por triangulo)
    lineVertexCount = lines.size() * 2; // 2 vertices por linha, numero_de_linhas*2
    fillTextBuff();

}

void Scene::fillTextBuff() {

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
