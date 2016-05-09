#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "include/FontAtlas.hpp"
#include "include/Graph.hpp"
#include "include/Scene.hpp"
#include "include/Config.hpp"

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

static GLFWwindow *setupGraphics(const Config& config) {
    if (!glfwInit()) {
        throw std::runtime_error{"Nao foi possivel inicializar a biblioteca GLFW 3"};
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(config.MultiSamples){
        glfwWindowHint(GLFW_SAMPLES, config.NumberOfSamples);
    }


    auto window = glfwCreateWindow(config.Width, config.Height, "Marvel Social Network", nullptr, nullptr);

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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (config.MultiSamples){
        glEnable(GL_MULTISAMPLE);
    }
    if (config.SmoothLines){
        glEnable(GL_LINE_SMOOTH);
    }
    glLineWidth(config.LineWidth);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}

int main(int argc, char *argv[]) {

    std::string configFile{"config.ini"};
    if(argc > 1){
        configFile = std::string{argv[1]};
    }

    auto config = Config::loadConfig(configFile);

    auto window = setupGraphics(config);

    auto atlas = FontAtlas{config.FontSize, config.FontPath};

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    auto scene = Scene{width, height, atlas};
    glfwSetWindowUserPointer(window, &scene);

    Graph graph{config.GraphPath};
    scene.fromGraph(graph, static_cast<Mode>(config.Mode), config.EdgeLimit);

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
