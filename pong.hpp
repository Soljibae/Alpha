#include "AEEngine.h"
#include <vector>

class Rect;

class GameState
{
public:
	GameState();

	void Init_Game();
	void Update_Game();
	void Exit_Game();

	bool GetisGameRunning();
	bool GetisGameStarted();

	void StartGame();

	void PrintTime();
	void PrintSquare();
	void DrawRect(float x, float y, float w, float h, float r, float g, float b, float a);
	void DrawRect(Rect& rect);

private:
	bool isGameRunning;
	bool isGameStarted;
	f64 start_time;
	f64 curr_time;
	s8 font;
	AEGfxVertexList* pMesh;
	AEMtx33 transforms;
};

struct Rect
{
public:
	float _x, _y;
	float _width, _height;
	float _r, _g, _b, _a;

	Rect(float x, float y, float width, float height, float r, float g, float b, float a);
};