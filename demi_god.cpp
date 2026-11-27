// demi_god.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game/God_Game.h"
#include <chrono>
#include <thread>

int main()
{
    God_Game *god_game = God_Game::getInstance();

    if (!god_game->initialize())
    {
        return false;
    }

    constexpr auto frame_interval = std::chrono::milliseconds(16);
    constexpr int demo_frame_count = 60;
    auto previous = std::chrono::steady_clock::now();
    for (int frame = 0; frame < demo_frame_count && god_game->isRunning(); ++frame)
    {
        std::this_thread::sleep_until(previous + frame_interval);
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
