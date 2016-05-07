#pragma once
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>
#include <array>

class Graphics {
public:
    Graphics(int width, int height);

    GLFWwindow *getWindow() const;

    int getWidth() const;

    int getHeight() const;
    Graphics(Graphics &&) = default;

    Graphics &operator=(Graphics &&) = default;

    virtual ~Graphics();
private:
    int width;
    int height;
    GLFWwindow *window;
    void setup();


};