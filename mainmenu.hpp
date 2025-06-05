#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "AEEngine.h"
#include "utils.hpp"

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	typedef enum
	{
		START,
		PONG,
		ANIMATION,
		EXIT
	} eMainMenuState;

	void Init_MainMenu();
	void Update_MainMenu();
	void Exit_MainMenu();

	eMainMenuState Get_Current_Menu_State();
private:
	eMainMenuState current_Menu_State;
	AEGfxVertexList* pMesh;
	AEMtx33 transform;
	s8 font;
	Rect pong_Button;
	Rect animation_Button;
	f64 delay;
};

#endif