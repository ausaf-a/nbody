#ifndef game_hpp
#define game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <random>

#include "body.hpp"

class Game
{

public:
    Game();
    ~Game();

    void init(const char *title, int x, int y, int w, int h, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning() { return running; };

private:
    bool running = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<Body> bodies;
    void addBody(int x, int y)
    {
        float vx = 0.01 * (((float)rand()) / RAND_MAX - 0.5);
        float vy = 0.01 * (((float)rand()) / RAND_MAX - 0.5);
        float m = 100.0 * ((float)rand()) / RAND_MAX;
        bodies.push_back(Body(x, y, vx, vy, m));
    }
};

#endif /* game_hpp */