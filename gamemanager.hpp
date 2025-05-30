#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "pong.hpp"

typedef enum
{
	SPLASHSCREEN,
	MAINMENU,
	PONG,
	ANIMATION,
	EXIT
} eGameState;

class GameState 
{
public:
	GameState();

	void Running_game();
	eGameState Get_Current_Game_State();
private:
	eGameState current_Game_State;
	Pong Pong_Manager;
};

#endif