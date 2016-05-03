#include "include/Graphics.hpp"
#include "include/Graph.hpp"
#include "include/Scene.hpp"

int main(int argc, char *argv[]) {


    Graphics graphics{1270, 720};
    auto window = graphics.getWindow();
    auto str = std::string{argv[1]};
    auto mode = std::atoi(argv[2]);
    int limit;
    if (argc > 3) {
        limit = std::atoi(argv[3]);
    } else {
        limit = 1000;
    }
    auto scene = Scene{graphics};

    Graph graph{str};
    scene.fromGraph(graph, static_cast<Mode>(mode), limit);

    SDL_Event event;
    while (true) {

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:
                    return 0;

                case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0) {
                        scene.zoom(0.8f);
                    } else if (event.wheel.y < 0) {
                        scene.zoom(1.2f);
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_MIDDLE) {
                        scene.resetZoom();
                    }
                    break;

                default:
                    break;
            }
        }

        scene.handleKeyboard();
        scene.draw();

        SDL_GL_SwapWindow(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    }

    return 0;
}