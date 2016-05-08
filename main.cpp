#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "include/FontAtlas.hpp"
#include "include/Graph.hpp"
#include "include/Scene.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

static void error_callback(int error, const char *description) {
    std::cerr << error << ": " << description << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    auto scene = static_cast<Scene *>(glfwGetWindowUserPointer(window));

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            scene->Keys[key] = true;
        else if (action == GLFW_RELEASE)
            scene->Keys[key] = false;
    }
}

static GLFWwindow *setupGraphics() {
    if (!glfwInit()) {
        throw std::runtime_error{"Nao foi possivel inicializar a biblioteca GLFW 3"};
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    auto window = glfwCreateWindow(WIDTH, HEIGHT, "Marvel Social Network", nullptr, nullptr);

    if (window == nullptr) {
        std::string erro{"Nao foi possivel iniciar a janela!"};
        throw std::runtime_error{erro};
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        throw std::runtime_error{std::string{"Nao foi possivel inicializar o glew! "}};
    }

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);

    //configua o viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSwapInterval(1);

    //glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}

int main(int argc, char *argv[]) {
    auto window = setupGraphics();
    auto str = std::string{argv[1]};
    auto mode = std::atoi(argv[2]);
    int limit;
    if (argc > 3) {
        limit = std::atoi(argv[3]);
    } else {
        limit = 1000;
    }

    auto atlas = FontAtlas{48, "Aileron.otf"};

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    auto scene = Scene{width, height, atlas};
    glfwSetWindowUserPointer(window, &scene);

    Graph graph{str};
    scene.fromGraph(graph, static_cast<Mode>(mode), limit);

    double deltaTime;
    double lastFrame = 0.0f;


    while (!glfwWindowShouldClose(window)) {
        auto currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
        scene.processInput(deltaTime);

        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene.draw();

    }

    glfwTerminate();
    return EXIT_SUCCESS;
}