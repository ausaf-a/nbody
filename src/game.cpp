
#include "game.hpp"
#include "body.hpp"

Game::Game()
{}

Game::~Game()
{
    this->clean();
}

void Game::init(const char *title, int x, int y, int w, int h, bool fullscreen)
{
    this->running = false;
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    // Initialize SDL, create window & renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL initialized successfully." << std::endl;
        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        this->running = true;
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            addBody(event.button.x, event.button.y);
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    for (int i = 0; i < bodies.size(); i++)
    {
        for (int j = i + 1; j < bodies.size(); j++)
        {
            bodies[i].applyGForce(bodies[j]);
            bodies[j].applyGForce(bodies[i]);
        }
        bodies[i].update();

        // Wrap off screen bodies to other side
        // if (bodies[i].pos[0] < 0)
        // {
        //     bodies[i].pos[0] = 600;
        // }
        // else if (bodies[i].pos[0] > 600)
        // {
        //     bodies[i].pos[0] = 0;
        // }
        // if (bodies[i].pos[1] < 0)
        // {
        //     bodies[i].pos[1] = 600;
        // }
        // else if (bodies[i].pos[1] > 600)
        // {
        //     bodies[i].pos[1] = 0;
        // }
    }
}

void Game::render()
{
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int c = 0; 
    for (int i = 0; i < bodies.size(); i++)
    {
        if (c == 0)
        {
            SDL_SetRenderDrawColor(renderer, 3, 140, 252, 255);
            c++; 
        }
        else if (c == 1)
        {
            SDL_SetRenderDrawColor(renderer, 144, 3, 252, 255);
            c++;
        }
        else if (c == 2)
        {
            SDL_SetRenderDrawColor(renderer, 252, 86, 3, 255);
            c = 0; 
        }

        bodies[i].draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
