#include "Game.h"

int main(int argc, char **argv)
{
    Game *guessit = new Game();

    if (guessit->is_running()) std::cout << "Running\n";

    do
    {
        while (guessit->is_running())
        {
            guessit->render();
            guessit->input();
            guessit->update();
        }
        if (guessit->getQuit()) break;
        SDL_Delay(2000);
        guessit->render("replay");
        guessit->input("replay");
        guessit->update("replay");
    } while (guessit->getReplay());

    delete guessit;

    return 0;
}
