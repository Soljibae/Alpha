#include "mainmenu.hpp"
#include "utils.hpp"

MainMenu::MainMenu()
	: transform{ 0 }
	, current_Menu_State(START)
	, pMesh(0)
	, font(AEGfxCreateFont("Assets/liberation-mono.ttf", 72))
	, pong_Button{ 0.f, 0.f, 320.f, 180.f, 0.5, 0.5, 0.5, 1.f }
	, animation_Button{ 0.f, 0.f, 320.f, 180.f, 0.5, 0.5, 0.5, 1.f }
	, delay{0.f}
{
	pong_Button._y = AEGfxGetWindowHeight() / 4.0f;
	animation_Button._y = -AEGfxGetWindowHeight() / 4.0f;
}

void MainMenu::Init_MainMenu()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh = AEGfxMeshEnd();

	delay = 0;
	current_Menu_State = START;
}

void MainMenu::Update_MainMenu()
{
	f64 dt = AEFrameRateControllerGetFrameTime();
	
	delay += dt;

	if (delay >= 0.3 && AEInputCheckTriggered(AEVK_ESCAPE))
		current_Menu_State = EXIT;

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	f32 text_width = 0;
	f32 text_height = 0;

	Draw_Shape(pong_Button, pMesh, transform, false);
	AEGfxGetPrintSize(font, "PONG", 0.5f, &text_width, &text_height);
	AEGfxPrint(font, "PONG", -text_width / 2, pong_Button._y * 2 / AEGfxGetWindowHeight() - text_height / 2, 0.5f, 1.f, 1.f, 1.f, 1);

	Draw_Shape(animation_Button, pMesh, transform, false);
	AEGfxGetPrintSize(font, "ANIMATON", 0.5f, &text_width, &text_height);
	AEGfxPrint(font, "ANIMATON", -text_width / 2, animation_Button._y * 2 / AEGfxGetWindowHeight() - text_height / 2, 0.5f, 1.f, 1.f, 1.f, 1);

	if(Is_Mouse_In_Square(pong_Button))
		if(AEInputCheckTriggered(AEVK_LBUTTON))
			current_Menu_State = PONG;

	if (Is_Mouse_In_Square(animation_Button))
		if (AEInputCheckTriggered(AEVK_LBUTTON))
			current_Menu_State = ANIMATION;
}

void MainMenu::Exit_MainMenu()
{
	AEGfxMeshFree(pMesh);
}

MainMenu::eMainMenuState MainMenu::Get_Current_Menu_State()
{
	return current_Menu_State;
}