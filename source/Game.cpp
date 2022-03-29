#include "Game.h"

int clicked[3] {-1,-1,-1};

void Game::generateNumber()
{
    srand((unsigned) time(0));
    this->secretNum = rand() % 999 + 1;
}

Game::Game()
{
    InitSDL(this->window, this->renderer);
    this->isRunning = true;

    this->font = TTF_OpenFont("assets/right.ttf", 70);

    this->background = new GameObject(this->renderer, "assets/bg.png");
    this->background->updatePosition(0,0,0.5);
    this->surround = new GameObject(this->renderer, "assets/surround.png");
    this->board = new GameObject(this->renderer, "assets/board.png");
    this->board->updatePosition(125, 80, 0.75);
    this->again = new GameObject(this->renderer, "assets/again.png");
    this->again->updatePosition(280,400,1); // waiting to be changed
    this->okay = new GameObject(this->renderer, "assets/okay.png");
    this->okay->updatePosition(600, 500, 0.5);
    this->bigger = new GameObject(this->renderer, "assets/bigger.png");
    this->bigger->updatePosition(200, 300, 0.4);
    this->smaller = new GameObject(this->renderer, "assets/smaller.png");
    this->smaller->updatePosition(200, 300, 0.4);
    this->correct = new GameObject(this->renderer, "assets/correct.png");
    this->correct->updatePosition(180, 300, 0.4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 10; ++j) {
            this->nums[i][j].setTexture(this->renderer, j);
            this->nums[i][j].updatePosition(40+70*j, 650+100*i, 0.4);
        }
    }

    generateNumber();
    this->currentNum = -1;
    std::cout << "Start game\n";
}

Game::~Game()
{
    QuitSDL(this->window, this->renderer);
    std::cout << "End game\n";
}

void Game::render()
{
    SDL_RenderClear(renderer);
    this->background->objRender(this->renderer);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 10; ++j) {
            this->nums[i][j].objRender(this->renderer);
        }
        if (clicked[i] >= 0) {
        this->surround->updatePosition(40+70*clicked[i]-4, 650+100*i+4, 0.05);
        this->surround->objRender(this->renderer);
        }
    }
    okay->objRender(this->renderer);
    board->objRender(this->renderer);
    if (currentNum > secretNum) {
        this->smaller->objRender(this->renderer);
    } else if (currentNum < secretNum) {
        if (currentNum != -1) this->bigger->objRender(this->renderer);
    } else this->correct->objRender(this->renderer);
    if (this->currentNum > 0) SDL_RenderCopy(this->renderer, text, nullptr, &desText);
    SDL_RenderPresent(this->renderer);

    SDL_Delay(20);
}

void Game::input()
{
    while (SDL_WaitEvent(&(this->event)))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int xm = event.button.x, ym = event.button.y;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 10; ++j) {
                    if (this->nums[i][j].checkClick(xm, ym))
                    {
                        clicked[i] = j;
                        goto NEXT;
                    }
                }
            }
            if (this->okay->checkClick(xm, ym)) {
                for (int i = 0; i < 3; ++i)
                    if (clicked[i] < 0) clicked[i] = 0;
                this->submit = true;
                goto NEXT;
            }
        }
        else if (event.type == SDL_QUIT)
        {
            this->isRunning = false;
            this->quit = true;
            break;
        }
        SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
    }
NEXT:
    {
    }
}

void Game::update()
{
    // game rule here
    if (this->submit)
    {
        currentNum = clicked[0]*100 + clicked[1]*10 + clicked[2];
        clicked[0] = clicked[1] = clicked[2] = -1;
        this->submit = false;
    }

    SDL_Surface* tsurface = TTF_RenderText_Solid(this->font, std::to_string(currentNum).c_str(), {0,0,0});
    this->text = SDL_CreateTextureFromSurface(this->renderer, tsurface);
    SDL_QueryTexture(this->text, nullptr, nullptr, &(this->desText.w), &(this->desText.h));
    desText.x = 300; desText.y = 170;
    SDL_FreeSurface(tsurface);

    if (currentNum == secretNum)
    {
        this->render();
        this->isRunning = false;
        currentNum = -1;
    }
    //
}

void Game::render(const char *random)
{
    SDL_RenderClear(renderer);
    this->background->objRender(this->renderer);
    this->again->objRender(this->renderer);

    SDL_RenderPresent(this->renderer);
    SDL_Delay(20);
}

void Game::input(const char *random)
{
    while(SDL_WaitEvent(&(this->event)))
    {
        int xm = event.button.x, ym = event.button.y;
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (this->again->checkClick(xm, ym))
            {
                this->setReplay();
                this->isRunning = true;
                generateNumber();
            }
            break;
        }
        else if (event.type == SDL_QUIT)
        {
            this->quit = true;
            break;
        }
    }
}

void Game::update(const char *random)
{

}
