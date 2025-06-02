#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "AEEngine.h"

class Character
{
public:
	Character();

	void Init_Character();
	void Update_Character();
	void Exit_Character();

	typedef enum
	{
		IDLE,
		WALK,
		JUMP,
		DEATH
	} eCharacterState;

private:
	eCharacterState current_Character_State;
	AEGfxTexture* pTex;
	AEGfxVertexList* pMesh;
	AEMtx33 transform;
	float _x, _y;
	const float _width, _height;
	float _u0, _u1;
	f64 animation_Time;
	int animaiton_Count;
	const int animaiton_Total_Count = 8;
};

#endif