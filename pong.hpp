#include "AEEngine.h"
#include <vector>

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

private:
	bool isGameRunning;
	bool isGameStarted;
	f64 start_time;
	f64 curr_time;
	s8 font;
	AEGfxVertexList* pMesh;
	AEMtx33 transforms;
};
