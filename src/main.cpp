#include "Game.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

int main()
{
    srand(time(0));
    //Initialize a new game
    Game game;
    //Run the game
    game.run();
}
