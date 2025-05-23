class GameState
{
public:
	GameState();

	void Init_Game();
	void Update_Game();
	void Exit_Game();

	bool GetisGameRunning();
private:
	bool isGameRunning;
};
