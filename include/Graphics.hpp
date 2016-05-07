#pragma once
#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>
#include <array>

class Graphics {
public:
    Graphics(int width, int height);

    SDL_Window *getWindow() const;

    int getWidth() const;

    int getHeight() const;
    Graphics(Graphics &&) = default;

    Graphics &operator=(Graphics &&) = default;

    virtual ~Graphics();
private:
    int width;
    int height;
    SDL_Window *window;
    SDL_GLContext glContext;
    void setup();


};