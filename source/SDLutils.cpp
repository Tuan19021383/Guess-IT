#include "SDLutils.h"

const char WINDOW_TITLE[] {"Guess it"};
const int SCREEN_WIDTH {600};
const int SCREEN_HEIGHT {800};

void InitSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) std::cout << "SDL_Init ! error\n";
    window = SDL_CreateWindow("Guess it", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == nullptr) std::cout << "window ! error\n";
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) std::cout << "renderer ! error\n";

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) std::cout << "IMG_Init ! error\n";
    if (TTF_Init() < 0) std::cout << "TTF_Init ! error\n";
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3) std::cout << "Mix_Init ! error\n";
}

void QuitSDL(SDL_Window*& window, SDL_Renderer*& renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
}
