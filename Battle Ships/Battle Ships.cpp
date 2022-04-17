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
#include <conio.h>

Player* m_player;
AI* m_AI;
void initialiseGame();
void gameLoop();



int main()
{
	/*while (true)
	{
		Input::KeyCode code = Input::getKeyFromPlayer();

		switch (code)
		{
		case Input::KeyCode::W:
			std::cout << "pressed W\n";
			break;
		case Input::KeyCode::A:
			std::cout << "pressed A\n";
			break;
		case Input::KeyCode::S:
			std::cout << "pressed S\n";
			break;
		case Input::KeyCode::D:
			std::cout << "pressed D\n";
			break;
		case Input::KeyCode::Up:
			std::cout << "pressed Up\n";
			break;
		case Input::KeyCode::Down:
			std::cout << "pressed Down\n";
			break;
		case Input::KeyCode::Left:
			std::cout << "pressed Left\n";
			break;
		case Input::KeyCode::Right:
			std::cout << "pressed Right\n";
			break;
		case Input::KeyCode::Enter:
			std::cout << "pressed Enter\n";
			break;
		case Input::KeyCode::Arrow:
			std::cout << "Arrow Pressed, Ignore this press\n";
			break;
		case Input::KeyCode::Default:
			std::cout << "Unrecognised Key\n";
			break;
		default:
			break;
		}
	}*/


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


