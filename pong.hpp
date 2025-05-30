#ifndef PONG_HPP
#define PONG_HPP

#include "AEEngine.h"
#include "utils.hpp"

class Pong
{
public:
	Pong();

	typedef enum
	{
		PRE_START,
		PLAYING,
		VICTORY,
		GAME_OVER
	} ePongState;

	void Init_Game();
	void Update_Game();
	void Exit_Game();

	void Start_Game();
	ePongState Get_Current_Game_State();

	void Init_Circle(Circle& circle);

	void Collision_Check_Player(Rect& rect, Circle& circle);
	void Collision_Check_Line(Circle& circle);
	void Collision_Check_PlayerGoal(Rect& rect, Circle& circle, float wall_x);
	bool CheckPlayerWin(Rect& rect1, Rect& rect2);
	void Update_Circle(Circle& circle, f64 dt);
	void Update_Rect(Rect& rect1, Rect& rect2, f64 dt);

	void Print_Time();
	void Print_Square();
	void Print_Circle();
	void Print_Score();
	void Print_Winner();

private:
	ePongState current_Game_State;
	f64 start_time;
	f64 curr_time;
	s8 font;
	AEGfxVertexList* pMesh;
	AEMtx33 transform;
	AEGfxTexture* pTex;
	Rect p1;
	Rect p2;
	Circle circle;
};

#endif