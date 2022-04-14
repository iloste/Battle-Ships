// Battle Ships.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Ship.h"
#include "Fleet.h"
#include "Grid.h"
#include <string>
#include "Player.h"
#include "AI.h"
#include <ctime>

Player* m_player;
AI* m_AI;
void initialiseGame();
void gameLoop();
void playersTurn();
void AIsTurn();


int main()
{
	initialiseGame();
	gameLoop();
}

void initialiseGame() {
	std::srand(std::time(nullptr));

	m_player = new Player();
	m_AI = new AI();

	m_player->setOpponent(m_AI);
	m_AI->setOpponent(m_player);
}

void gameLoop() {
	bool gameRunning = true;

	while (gameRunning)
	{
#pragma region players turn
		m_player->takeTurn();

		if (m_AI->fleetDestroyed())
		{
			Output::printInColour("Player Won!", Output::Colour::Green);
			gameRunning = false;
			break;
		}
#pragma endregion

#pragma region AIs turn
		m_AI->takeTurn();

		if (m_AI->fleetDestroyed())
		{
			Output::printInColour("Player Lost!", Output::Colour::Red);
			gameRunning = false;
			break;
		}
#pragma endregion

	}
}


