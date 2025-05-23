#include "pong.hpp"
#include "AEEngine.h"
#include <string>
#include <sstream>
#include <iomanip>

Rect p1{ -600, 0, 70, 250, 1.f, 0.f, 1.f, 1.f };
Rect p2{ 600, 0, 70, 250, 0.f, 1.f, 1.f, 1.f };

GameState::GameState()
	:transforms{ 0 }
{
	isGameRunning = true;
	isGameStarted = false;
	start_time = 0;
	curr_time = 0;
	font = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);
	pMesh = 0;
}

void GameState::Init_Game()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	pMesh = AEGfxMeshEnd();
	
	
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

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	PrintSquare();
	PrintTime();
}

void GameState::Exit_Game()
{
	AEGfxMeshFree(pMesh);
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
	AEGfxPrint(font, time.c_str(), - text_width / 2, 0.8f, 0.5f, 1.f, 1.f, 1.f, 1);
}

void GameState::PrintSquare()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	DrawRect(p1);
	
	DrawRect(-800, 0, 40, 900, 1.f, 0.f, 1.f, 1.f);

	DrawRect(p2);

	DrawRect(800, 0, 40, 900, 0.f, 1.f, 1.f, 1.f);
}

void GameState::DrawRect(float x, float y, float w, float h, float r, float g, float b, float a)
{
	AEMtx33 scale;
	AEMtx33Scale(&scale, w, h);

	AEMtx33 tran;
	AEMtx33Trans(&tran, x, y);

	AEMtx33Concat(&transforms, &tran, &scale);

	AEGfxSetColorToMultiply(0.f, 0.f, 0.f, 0.f);

	AEGfxSetColorToAdd(r, g, b, a);

	AEGfxSetTransform(transforms.m);

	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

void  GameState::DrawRect(Rect& rect)
{
	AEMtx33 scale;
	AEMtx33Scale(&scale, rect._width, rect._height);
	AEMtx33 tran;
	AEMtx33Trans(&tran, rect._x, rect._y);

	AEMtx33Concat(&transforms, &tran, &scale);

	AEGfxSetColorToMultiply(0.f, 0.f, 0.f, 0.f);

	AEGfxSetColorToAdd(rect._r, rect._g, rect._b, rect._a);

	AEGfxSetTransform(transforms.m);

	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}