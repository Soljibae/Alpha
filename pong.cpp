#include "pong.hpp"
#include "AEEngine.h"

GameState::GameState()
{
	isGameRunning = true;
}

void GameState::Init_Game()
{
	s8 font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
}

void GameState::Update_Game()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		isGameRunning = false;
}

void GameState::Exit_Game()
{

}

bool GameState::GetisGameRunning()
{
	return isGameRunning;
}
