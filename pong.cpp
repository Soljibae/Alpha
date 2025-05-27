#include "pong.hpp"
#include "AEEngine.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>

GameState::GameState()
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

GameState::Shape::Shape(float x, float y, float width, float height, float r, float g, float b, float a) :_x(x), _y(y), _width(width), _height(height), _r(r), _g(g), _b(b), _a(a) {}

GameState::Rect::Rect(float x, float y, float width, float height, float r, float g, float b, float a) : Shape(x, y, width, height, r, g, b, a), score(0) {}

GameState::Circle::Circle(float x, float y, float width, float height, float r, float g, float b, float a) : Shape(x, y, width, height, r, g, b, a)
{
	AEVec2Zero(&moving_vector);
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

	Init_Circle(circle);
}

void GameState::Update_Game()
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

		Collision_Check_Line(circle);

		Collision_Check_PlayerGoal(p1, circle, AEGfxGetWindowWidth() / 2 - 20);

		Collision_Check_PlayerGoal(p2, circle, -AEGfxGetWindowWidth() / 2 + 20);

		Collision_Check_Player(p1, circle);

		Collision_Check_Player(p2, circle);

		Update_Circle(circle, dt * 600);

	}

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	Print_Square();
	Print_Circle();
	Print_Time();
}

void GameState::Exit_Game()
{
	AEGfxMeshFree(pMesh);
	AEGfxTextureUnload(pTex);
}

void GameState::Start_Game()
{
	current_Game_State = PLAYING;
	start_time = AEGetTime(nullptr);
}

GameState::eGameState GameState::Get_Current_Game_State()
{
	return current_Game_State;
}

void GameState::Init_Circle(Circle& circle)
{
	static std::mt19937 gen{ std::random_device{}() };
	std::uniform_real_distribution<float> dist(-1, 1);

	circle._x = 0;
	circle._y = 0;

	AEVec2Set(&circle.moving_vector, dist(gen), dist(gen));
	AEVec2Normalize(&circle.moving_vector, &circle.moving_vector);
}

void GameState::Collision_Check_Player(Rect& rect, Circle& circle)
{
	AEVec2 closest_point, circle_vector;
	AEVec2Set(&circle_vector, circle._x, circle._y);
	AEVec2Set(&closest_point, std::clamp(circle._x, rect._x - rect._width / 2, rect._x + rect._width / 2), std::clamp(circle._y, rect._y - rect._height / 2, rect._y + rect._height / 2));

	if (AEVec2Distance(&circle_vector, &closest_point) <= circle._width / 2)
	{
		if (closest_point.x == rect._x - rect._width / 2 || closest_point.x == rect._x + rect._width / 2)
		{
			circle.moving_vector.x *= -1;
		}
		if (closest_point.y == rect._y - rect._height / 2 || closest_point.y == rect._y + rect._height / 2)
		{
			circle.moving_vector.y *= -1;
		}
	}
}

void GameState::Collision_Check_Line(Circle& circle)
{
	if (AEGfxGetWindowHeight() / 2 - circle._y < circle._height / 2 || AEGfxGetWindowHeight() / 2 + circle._y < circle._height / 2)
		circle.moving_vector.y *= -1;
}

void GameState::Collision_Check_PlayerGoal(Rect& rect, Circle& circle, float wall_x)
{
	if ((wall_x - circle._x) * (wall_x - circle._x) < (circle._width / 2) * (circle._width / 2))
	{
		circle.moving_vector.x *= -1;
		rect.score++;
	}
}

void GameState::Update_Circle(Circle& circle, f64 dt)
{
	circle._x += circle.moving_vector.x * dt;
	circle._y += circle.moving_vector.y * dt;
}

void GameState::Print_Time()
{
	static int curr_min = 0;
	static int curr_sec = 0;

	f32 text_width = 0;
	f32 text_height = 0;

	std::ostringstream oss;

	oss << std::setw(2) << std::setfill('0') << curr_min << ':' << std::setw(2) << std::setfill('0') << curr_sec;

	std::string time = oss.str();

	if (current_Game_State == PLAYING)
	{
		curr_time = AEGetTime(nullptr) - start_time;
		curr_min = static_cast<int>(curr_time / 60);
		curr_sec = static_cast<int>(curr_time) % 60;
	}

	AEGfxGetPrintSize(font, time.c_str(), 0.5f, &text_width, &text_height);
	AEGfxPrint(font, time.c_str(), -text_width / 2, 0.8f, 0.5f, 1.f, 1.f, 1.f, 1);
}

void GameState::Print_Square()
{
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	Draw_Shape(p1);

	Draw_Shape(-AEGfxGetWindowWidth() / 2, 0, 40, AEGfxGetWindowHeight(), 1.f, 0.f, 1.f, 1.f);

	Draw_Shape(p2);

	Draw_Shape(AEGfxGetWindowWidth() / 2, 0, 40, AEGfxGetWindowHeight(), 0.f, 1.f, 1.f, 1.f);
}

void GameState::Print_Circle()
{
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex, 0, 0);

	Draw_Shape(circle);
}

void GameState::Draw_Shape(float x, float y, float w, float h, float r, float g, float b, float a)
{
	Rect shape(x, y, w, h, r, g, b, a);

	Draw_Shape(shape);
}

void  GameState::Draw_Shape(Shape& shape)
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
