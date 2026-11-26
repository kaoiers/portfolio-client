// demi_god.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game/God_Game.h"

int main()
{
    God_Game *god_game = God_Game::getInstance();

    if (!god_game->initialize())
    {
        return false;
    }

    while (god_game->isRunning())
    {
        god_game->control();

        god_game->update(0);

        god_game->render();
    }

    god_game->gameReset();

    return 0;
}
