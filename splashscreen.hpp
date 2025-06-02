
class SplashScreen
{
public:
	SplashScreen();

	typedef enum
	{
		START,
		END
	} eSplashScreenState;

	void Init_SplashScreen();
	void Update_SplashScreen();
	void Exit_SplashScreen();

	eSplashScreenState Get_Current_Game_State();
private:
	eSplashScreenState current_Screen_State;
	AEGfxVertexList* pMesh;
	AEMtx33 transform;
	AEGfxTexture* pTex;
	Rect title;
	f64 screen_Time;
};