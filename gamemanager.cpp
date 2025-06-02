#include "AEEngine.h"
#include "gamemanager.hpp"

GameState::GameState()
	: current_Game_State(SPLASHSCREEN) { }

void GameState::Running_game()
{
	while (current_Game_State != EXIT)
	{
		if (current_Game_State == SPLASHSCREEN)
		{
			Splash_Screen_Manager.Init_SplashScreen();

			while (Splash_Screen_Manager.Get_Current_Game_State() != SplashScreen::END)
			{
				AESysFrameStart();

				Splash_Screen_Manager.Update_SplashScreen();

				AESysFrameEnd();
			}

			if (Splash_Screen_Manager.Get_Current_Game_State() == SplashScreen::END)
			{
				Splash_Screen_Manager.Exit_SplashScreen();
				current_Game_State = PONG;
			}
		}

		if (current_Game_State == PONG)
		{
			Pong_Manager.Init_Game();

			while (Pong_Manager.Get_Current_Game_State() != Pong::GAME_OVER)
			{
				AESysFrameStart();

				Pong_Manager.Update_Game();

				AESysFrameEnd();
			}

			if (Pong_Manager.Get_Current_Game_State() == Pong::GAME_OVER)
			{
				Pong_Manager.Exit_Game();
				current_Game_State = EXIT;
			}
		}
	}	
}

eGameState GameState::Get_Current_Game_State()
{
	return current_Game_State;
}

