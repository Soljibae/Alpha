#include "pong.hpp"
#include "AEEngine.h"
#include <string>
#include <sstream>
#include <iomanip>

Shape p1{ -600, 0, 70, 250, 1.f, 0.f, 1.f, 1.f };
Shape p2{ 600, 0, 70, 250, 0.f, 1.f, 1.f, 1.f };
Shape circle{ 0, 0, 50, 50, 1.f, 1.f, 1.f, 1.f };

GameState::GameState()
	:transform{ 0 }
{
	currentGameState = PRE_START;
	start_time = 0;
	curr_time = 0;
	font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
	pMesh = 0;
	pTex = AEGfxTextureLoad("Assets/circle.png");
}

void GameState::Init_Game()
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


}

void GameState::Update_Game()
{
	if (AEInputCheckTriggered(VK_SPACE))
	{
		if (currentGameState == PRE_START)
		{
			StartGame();
			start_time = AEGetTime(nullptr);
		}
	}

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		currentGameState = GAME_OVER;


	if (currentGameState == PLAYING)
	{

		if (AEInputCheckTriggered(AEVK_R))
		{
			Init_Game();
			start_time = AEGetTime(nullptr);
		}

	}

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	PrintSquare();
	PrintCircle();
	PrintTime();
}

void GameState::Exit_Game()
{
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
}

void GameState::StartGame()
{
	currentGameState = PLAYING;
}

eGameState GameState::GetcurrentGameState()
{
	return currentGameState;
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

	if (currentGameState == PLAYING)
	{
		curr_time = AEGetTime(nullptr) - start_time;
		curr_min = static_cast<int>(curr_time / 60);
		curr_sec = static_cast<int>(curr_time) % 60;
	}

	AEGfxGetPrintSize(font, time.c_str(), 0.5, &text_width, &text_height);
	AEGfxPrint(font, time.c_str(), -text_width / 2, 0.8f, 0.5f, 1.f, 1.f, 1.f, 1);
}

void GameState::PrintSquare()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	DrawShape(p1);

	DrawShape(-800, 0, 40, 900, 1.f, 0.f, 1.f, 1.f);

	DrawShape(p2);

	DrawShape(800, 0, 40, 900, 0.f, 1.f, 1.f, 1.f);
}

void GameState::PrintCircle()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex, 0, 0);

	DrawShape(circle);
}

void GameState::DrawShape(float x, float y, float w, float h, float r, float g, float b, float a)
{
	Shape shape(x, y, w, h, r, g, b, a);

	DrawShape(shape);
}

void  GameState::DrawShape(Shape& shape)
{
	AEMtx33 scale;
	AEMtx33Scale(&scale, shape._width, shape._height);
	AEMtx33 tran;
	AEMtx33Trans(&tran, shape._x, shape._y);

	AEMtx33Concat(&transform, &tran, &scale);

	AEGfxSetColorToMultiply(0.f, 0.f, 0.f, 0.f);

	AEGfxSetColorToAdd(shape._r, shape._g, shape._b, shape._a);

	AEGfxSetTransform(transform.m);

	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

Shape::Shape(float x, float y, float width, float height, float r, float g, float b, float a) :_x(x), _y(y), _width(width), _height(height), _r(r), _g(g), _b(b), _a(a) {}