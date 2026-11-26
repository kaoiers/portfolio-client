// demi_god.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game/God_Game.h"
#include <chrono>

int main()
{
    God_Game *god_game = God_Game::getInstance();

    if (!god_game->initialize())
    {
        return false;
    }

    auto previous = std::chrono::steady_clock::now();
    while (god_game->isRunning())
    {
        god_game->control();

        const auto now = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - previous);
        previous += elapsed;
        god_game->update(static_cast<u32>(elapsed.count()));

        god_game->render();
    }

    god_game->gameReset();

    return 0;
}
