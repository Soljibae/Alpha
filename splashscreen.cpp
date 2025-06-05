
#include "utils.hpp"
#include "splashscreen.hpp"

SplashScreen::SplashScreen()
	: transform{ 0 }
	, current_Screen_State(START)
	, pMesh(0)
	, pTex(AEGfxTextureLoad("Assets/DigiPen_WHITE.png"))
	, title{ 0.f, 0.f, 1048.f, 256.f, 1.f, 1.f, 1.f, 0.f }
	, screen_Time(0.f)
{
}

void SplashScreen::Init_SplashScreen()
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

	current_Screen_State = START;
}

void SplashScreen::Update_SplashScreen()
{
	f64 dt = AEFrameRateControllerGetFrameTime();

	if (AEInputCheckTriggered(AEVK_SPACE))
		current_Screen_State = END;

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex, 0, 0);
	
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	Draw_Shape(title, pMesh, transform, true);

	screen_Time += dt;

	if (screen_Time <= 2.f)
		title._a += static_cast<float>(dt) / 2.f;
	else if (screen_Time >= 2.5)
		title._a -= static_cast<float>(dt) / 2.f;

	if (screen_Time >= 4.5)
		current_Screen_State = END;
}

void SplashScreen::Exit_SplashScreen()
{
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
}

SplashScreen::eSplashScreenState SplashScreen::Get_Current_Game_State()
{
	return current_Screen_State;
}