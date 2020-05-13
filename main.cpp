#include "game.hpp"

Game *g = nullptr;

int main(int argc, char *argv[])
{
    g = new Game(); 
    g->init("N-Body Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (g->isRunning())
    {
        g->handleEvents();
        g->update();
        g->render();
    }

    g->clean();
    return 0;
}