#include "AEEngine.h"
#include <vector>



class GameState
{
public:
	GameState();

	typedef enum
	{
		PRE_START,
		PLAYING,
		GAME_OVER
	} eGameState;

	struct Shape
	{
		float _x, _y;
		float _width, _height;
		float _r, _g, _b, _a;

		Shape(float x, float y, float width, float height, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
	};

	struct Rect : public Shape
	{
		int score;

		Rect(float x, float y, float width, float height, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
	};

	struct Circle : public Shape
	{
		AEVec2 moving_vector;

		Circle(float x, float y, float width, float height, float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f);
	};

	void Init_Game();
	void Update_Game();
	void Exit_Game();

	void Start_Game();
	eGameState Get_Current_Game_State();

	void Init_Circle(Circle& circle);

	void Collision_Check_Player(Rect& rect, Circle& circle);
	void Collision_Check_Line(Circle& circle);
	void Collision_Check_PlayerGoal(Rect& rect, Circle& circle, float wall_x);
	void Update_Circle(Circle& circle, f64 dt);

	void Print_Time();
	void Print_Square();
	void Print_Circle();
	void Draw_Shape(float x, float y, float w, float h, float r, float g, float b, float a);
	void Draw_Shape(Shape& shape);

private:
	eGameState current_Game_State;
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

