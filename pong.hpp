#include "AEEngine.h"
#include <vector>

typedef enum
{
	PRE_START,
	PLAYING,
	GAME_OVER
} eGameState;

struct Shape;

class GameState
{
public:
	GameState();

	void Init_Game();
	void Update_Game();
	void Exit_Game();

	void StartGame();

	eGameState GetcurrentGameState();

	void PrintTime();
	void PrintSquare();
	void PrintCircle();
	void DrawShape(float x, float y, float w, float h, float r, float g, float b, float a);
	void DrawShape(Shape& shape);

private:
	eGameState currentGameState;
	f64 start_time;
	f64 curr_time;
	s8 font;
	AEGfxVertexList* pMesh;
	AEMtx33 transform;
	AEGfxTexture* pTex;
};

struct Shape
{
public:
	float _x, _y;
	float _width, _height;
	float _r, _g, _b, _a;

	Shape(float x, float y, float width, float height, float r, float g, float b, float a);
};