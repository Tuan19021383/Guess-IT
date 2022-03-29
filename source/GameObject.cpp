#include "GameObject.h"

void GameObject::setTexture(SDL_Renderer*& renderer, const char* filepath)
{
    SDL_Surface* surface = IMG_Load(filepath);
    this->objTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (this->objTexture == nullptr) std::cout << "setTexture ! error : " << filepath << std::endl;
    SDL_FreeSurface(surface);

    SDL_QueryTexture(this->objTexture, nullptr, nullptr, &(this->srcRect.w), &(this->srcRect.h));
}

void GameObject::setTexture(SDL_Renderer*& renderer, int num)
{
    switch(num) {
    case 0:
        this->setTexture(renderer, "./assets/0.png");
        break;
    case 1:
        this->setTexture(renderer, "./assets/1.png");
        break;
    case 2:
        this->setTexture(renderer, "./assets/2.png");
        break;
    case 3:
        this->setTexture(renderer, "./assets/3.png");
        break;
    case 4:
        this->setTexture(renderer, "./assets/4.png");
        break;
    case 5:
        this->setTexture(renderer, "./assets/5.png");
        break;
    case 6:
        this->setTexture(renderer, "./assets/6.png");
        break;
    case 7:
        this->setTexture(renderer, "./assets/7.png");
        break;
    case 8:
        this->setTexture(renderer, "./assets/8.png");
        break;
    case 9:
        this->setTexture(renderer, "./assets/9.png");
        break;
    default:
        break;
    }
}

GameObject::GameObject(SDL_Renderer*& renderer, const char* filepath)
{
    this->setTexture(renderer, filepath);
}

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
    SDL_DestroyTexture(objTexture);
}

void GameObject::objRender(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer, this->objTexture, nullptr, &(this->desRect));
}

void GameObject::updatePosition(int xpos, int ypos, double scale)
{
    this->desRect.x = xpos;
    this->desRect.y = ypos;
    this->desRect.w = this->srcRect.w * scale;
    this->desRect.h = this->srcRect.h * scale;
}

bool GameObject::checkClick(int xmouse, int ymouse)
{
    if (xmouse > this->desRect.x
        && xmouse < this->desRect.w+this->desRect.x
        && ymouse > this->desRect.y
        && ymouse < this->desRect.h + this->desRect.y)
        return true;
    else return false;
}
