#include "AEEngine.h"

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
private:
	bool isGameRunning;
	bool isGameStarted;
	f64 start_time;
	f64 curr_time;
	s8 font;
};
