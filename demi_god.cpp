// demi_god.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "game/God_Game.h"

int main()
{
	God_Game *godGame = God_Game::GetInstance();

	if (!godGame->Initialize())
	{
		return false;
	}

	while (godGame->isRunning())
	{

		godGame->control();

		godGame->upadte(0);

		godGame->render();

	}

	godGame->GameReset();

    return 0;
}

