#include "pong.hpp"
#include "AEEngine.h"
#include <string>
#include <sstream>
#include <iomanip>

GameState::GameState()
{
	isGameRunning = true;
	isGameStarted = false;
	start_time = 0;
	curr_time = 0;
	font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
}

void GameState::Init_Game()
{

}

void GameState::Update_Game()
{
	if (AEInputCheckTriggered(VK_SPACE) || 0 == AESysDoesWindowExist())
	{
		if (isGameStarted == false)
		{
			StartGame();
			start_time = AEGetTime(nullptr);
		}
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		isGameRunning = false;
	

	if (isGameStarted)
	{

		if (AEInputCheckTriggered(AEVK_R) || 0 == AESysDoesWindowExist())
		{
			Init_Game();
			start_time = AEGetTime(nullptr);
		}
		
	}

	PrintTime();
}

void GameState::Exit_Game()
{

}

bool GameState::GetisGameRunning()
{
	return isGameRunning;
}

bool GameState::GetisGameStarted()
{
	return isGameStarted;
}

void GameState::StartGame()
{
	isGameStarted = true;
}

void GameState::PrintTime()
{
	static int curr_min = 0;
	static int curr_sec = 0;

	f32 text_width = 0;
	f32 text_height = 0;

	std::ostringstream oss;

	oss << std::setw(2) << std::setfill('0') << curr_min << ':' << std::setw(2) << std::setfill('0') << curr_sec;

	std::string time = oss.str();

	if (isGameStarted)
	{
		curr_time = AEGetTime(nullptr) - start_time;
		curr_min = static_cast<int>(curr_time / 60);
		curr_sec = static_cast<int>(curr_time) % 60;
	}

	AEGfxGetPrintSize(font, time.c_str(), 0.5, &text_width, &text_height);
	AEGfxPrint(font, time.c_str(), - text_width / 2, 0.8, 0.5, 0, 0, 0, 1);
}