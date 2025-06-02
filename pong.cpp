#include "pong.hpp"
#include "gamemanager.hpp"
#include "AEEngine.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <cmath>

Pong::Pong()
	: transform{ 0 }
	, current_Game_State(PRE_START)
	, start_time(0)
	, curr_time(0)
	, font(AEGfxCreateFont("Assets/liberation-mono.ttf", 72))
	, pMesh(0)
	, pTex(AEGfxTextureLoad("Assets/circle.png"))
	, p1{ -600, 0, 70, 250, 1.f, 0.f, 1.f, 1.f }
	, p2{ 600, 0, 70, 250, 0.f, 1.f, 1.f, 1.f }
	, circle{ 0, 0, 50, 50 }
{
}


void Pong::Init_Game()
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

	pTex = AEGfxTextureLoad("Assets/circle.png");

	current_Game_State = PRE_START;

	p1._y = 0;
	p2._y = 0;

	p1.score = 0;
	p2.score = 0;

	Init_Circle(circle);
}

void Pong::Update_Game()
{
	f64 dt = AEFrameRateControllerGetFrameTime();

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		current_Game_State = GAME_OVER;

	if (current_Game_State == PRE_START)
	{
		if (AEInputCheckTriggered(VK_SPACE))
		{
			Start_Game();
		}
	}

	if (current_Game_State == PLAYING)
	{
		if (AEInputCheckTriggered(AEVK_R))
		{
			Init_Game();
			Start_Game();
		}

		Update_Rect(p1, p2, dt);

		Update_Circle(circle, dt);

		Collision_Check_Player(p1, circle);

		Collision_Check_Player(p2, circle);

		Collision_Check_PlayerGoal(p1, circle, AEGfxGetWindowWidth() / 2 - 20);

		Collision_Check_PlayerGoal(p2, circle, -AEGfxGetWindowWidth() / 2 + 20);

		Collision_Check_Line(circle);

		if (CheckPlayerWin(p1, p2))
		{
			current_Game_State = VICTORY;
		}
	}

	if (current_Game_State == VICTORY)
	{
		if (AEInputCheckTriggered(AEVK_R))
		{
			Init_Game();
			Start_Game();
		}
		Print_Winner();
	}

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	Print_Square();
	Print_Circle();
	Print_Time();
	Print_Score();
}

void Pong::Exit_Game()
{
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
}

void Pong::Start_Game()
{
	current_Game_State = PLAYING;
	start_time = AEGetTime(nullptr);
}

Pong::ePongState Pong::Get_Current_Game_State()
{
	return current_Game_State;
}

void Pong::Init_Circle(Circle& circle)
{
	static std::mt19937 gen{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(-1, 1);

	circle._x = 0;
	circle._y = 0;
	circle.speed = 600;

	AEVec2Set(&circle.moving_vector, dist(gen), dist(gen));
	AEVec2Normalize(&circle.moving_vector, &circle.moving_vector);
}

void Pong::Collision_Check_Player(Rect& rect, Circle& circle)
{
	const float radius = circle._width * 0.5f;
	const float halfW = rect._width * 0.5f;
	const float halfH = rect._height * 0.5f;

	float dx = circle._x - rect._x;
	float dy = circle._y - rect._y;

	if (std::fabs(dx) < halfW + radius &&
		std::fabs(dy) < halfH + radius)
	{

		AEVec2 changed_vector;
		AEVec2 circel_vector;
		AEVec2 rect_vector;
		AEVec2Set(&circel_vector, circle._x, circle._y);
		AEVec2Set(&rect_vector, rect._x, rect._y);
		AEVec2Sub(&changed_vector, &circel_vector, &rect_vector);
		AEVec2Normalize(&changed_vector, &changed_vector);
		
		circle.moving_vector = changed_vector;

		circle.speed = 1600;            
	}
}

void Pong::Collision_Check_Line(Circle& circle)
{
	float halfH = AEGfxGetWindowHeight() / 2.0f;
	float radius = circle._height / 2.0f;

	if (circle._y + radius > halfH)
	{
		circle._y = halfH - radius;
		circle.moving_vector.y *= -1;
	}

	else if (circle._y - radius < -halfH)
	{
		circle._y = -halfH + radius;
		circle.moving_vector.y *= -1;
	}
}

void Pong::Collision_Check_PlayerGoal(Rect& rect, Circle& circle, float wall_x)
{
	if ((wall_x - circle._x) * (wall_x - circle._x) < (circle._width / 2) * (circle._width / 2))
	{
		circle.moving_vector.x *= -1;
		rect.score++;
	}
}

bool  Pong::CheckPlayerWin(Rect& rect1, Rect& rect2)
{
	if (rect1.score == 11 || rect2.score == 11)
		return true;

	return false;
}

void Pong::Update_Circle(Circle& circle, f64 dt)
{
	circle.speed = std::clamp(circle.speed - static_cast<float>(dt) * 200, static_cast<float>(800), static_cast<float>(1600));

	circle._x += circle.moving_vector.x * (dt * circle.speed);
	circle._y += circle.moving_vector.y * (dt * circle.speed);
}

void Pong::Update_Rect(Rect& rect1, Rect& rect2, f64 dt)
{
	if (AEInputCheckCurr(AEVK_W))
	{
		rect1._y = std::clamp(rect1._y + static_cast<float>(dt) * 1000, -AEGfxGetWindowHeight() / 2 + rect1._height / 2, AEGfxGetWindowHeight() / 2 - rect1._height / 2);
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		rect1._y = std::clamp(rect1._y - static_cast<float>(dt) * 1000, -AEGfxGetWindowHeight() / 2 + rect1._height / 2, AEGfxGetWindowHeight() / 2 - rect1._height / 2);
	}

	s32 mouse_x = 0;
	s32 mouse_y = 0;

	AEInputGetCursorPosition(&mouse_x, &mouse_y);

	mouse_y = AEGfxGetWindowHeight() / 2.0f - static_cast<float>(mouse_y);

	if (std::fabs(rect2._y - mouse_y) >= 30.f)
	{
		if (rect2._y < mouse_y)
		{
			rect2._y = std::clamp(rect2._y + static_cast<float>(dt) * 1000, -AEGfxGetWindowHeight() / 2 + rect2._height / 2, AEGfxGetWindowHeight() / 2 - rect2._height / 2);
		}
		else
		{
			rect2._y = std::clamp(rect2._y - static_cast<float>(dt) * 1000, -AEGfxGetWindowHeight() / 2 + rect2._height / 2, AEGfxGetWindowHeight() / 2 - rect2._height / 2);
		}
	}
}

void Pong::Print_Time()
{
	static int curr_min = 0;
	static int curr_sec = 0;

	f32 text_width = 0;

	std::ostringstream oss;

	oss << std::setw(2) << std::setfill('0') << curr_min << ':' << std::setw(2) << std::setfill('0') << curr_sec;

	std::string time = oss.str();

	if (current_Game_State == PLAYING)
	{
		curr_time = AEGetTime(nullptr) - start_time;
		curr_min = static_cast<int>(curr_time / 60);
		curr_sec = static_cast<int>(curr_time) % 60;
	}

	AEGfxGetPrintSize(font, time.c_str(), 0.5f, &text_width, 0);
	AEGfxPrint(font, time.c_str(), -text_width / 2, 0.8f, 0.5f, 1.f, 1.f, 1.f, 1);
}

void Pong::Print_Square()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	Draw_Shape(p1, pMesh, transform);

	Draw_Shape(-AEGfxGetWindowWidth() / 2, 0, 40, AEGfxGetWindowHeight(), 1.f, 0.f, 1.f, 1.f, pMesh, transform);

	Draw_Shape(p2, pMesh, transform);

	Draw_Shape(AEGfxGetWindowWidth() / 2, 0, 40, AEGfxGetWindowHeight(), 0.f, 1.f, 1.f, 1.f, pMesh, transform);
}

void Pong::Print_Circle()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex, 0, 0);

	Draw_Shape(circle, pMesh, transform);
}

void Pong::Print_Score()
{
	std::ostringstream oss;

	f32 text_width = 0;

	oss << std::setw(2) << std::setfill('0') << p1.score;

	AEGfxGetPrintSize(font, oss.str().c_str(), 0.5f, &text_width, 0);
	AEGfxPrint(font, oss.str().c_str(), -0.25f -text_width / 2, 0.75f, 0.6f, 1.f, 1.f, 1.f, 1);

	oss.str("");
	oss.clear();

	oss << std::setw(2) << std::setfill('0') << p2.score;

	AEGfxGetPrintSize(font, oss.str().c_str(), 0.5f, &text_width, 0);
	AEGfxPrint(font, oss.str().c_str(), 0.25 - text_width / 2, 0.75f, 0.6f, 1.f, 1.f, 1.f, 1);
}

void Pong::Print_Winner()
{
	f32 text_width = 0;

	if (p1.score == 11)
	{
		AEGfxGetPrintSize(font, "WIN", 0.5f, &text_width, 0);
		AEGfxPrint(font, "WIN", -0.25f - text_width / 2, 0.6f, 0.6f, 1.f, 1.f, 1.f, 1);
	}

	if (p2.score == 11)
	{
		AEGfxGetPrintSize(font, "WIN", 0.5f, &text_width, 0);
		AEGfxPrint(font, "WIN", 0.25 - text_width / 2, 0.6f, 0.6f, 1.f, 1.f, 1.f, 1);
	}
}

