#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#ifndef SDLUTILS_H
#define SDLUTILS_H

void InitSDL(SDL_Window*& window, SDL_Renderer*& renderer);

void QuitSDL(SDL_Window*& window, SDL_Renderer*& renderer);

#endif /* end of include guard: SDLUTILS_H */
