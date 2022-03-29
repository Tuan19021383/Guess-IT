#include "SDLutils.h"
#include <fstream>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
    GameObject(SDL_Renderer*& renderer, const char* filepath);
    GameObject(SDL_Renderer*& renderer, int num);
    GameObject();
    ~GameObject();
    void setTexture(SDL_Renderer*& renderer, const char* filepath);
    void setTexture(SDL_Renderer*& renderer, int num);
    void objRender(SDL_Renderer*& renderer);
    void updatePosition(int xpos, int ypos, double scale);
    bool checkClick(int xmouse, int ymouse);
private:
    SDL_Texture* objTexture = NULL;
    SDL_Rect srcRect {0,0,0,0};
    SDL_Rect desRect {0,0,0,0};
};

#endif
