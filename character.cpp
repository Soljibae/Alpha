#include "character.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>

Character::Character()
	: current_Character_State(IDLE)
	, pTex{}
	, pMesh(0)
	, transform{ 0 }
	, _x(0.f)
	, _y(0.f)
	, _width(384.f / 4.f)
	, _height(64.f * 2.f)
	, _offset(0.f)
	, animation_Time(0.f)
	, animaiton_Count(0)
	, isFacingRight(true)
{
}

Character::~Character()
{
	if (pMesh)
		AEGfxMeshFree(pMesh);
	for (int i = 0; i < MAX_CNT; i++)
	{
		if (pTex[i])
			AEGfxTextureUnload(pTex[i]);
	}
	
}

void Character::Init_Character()
{
	if (pMesh)
		AEGfxMeshFree(pMesh);
	for (int i = 0; i < MAX_CNT; i++)
	{
		if (pTex[i])
			AEGfxTextureUnload(pTex[i]);
	}

	_x = 0.f;
	_y = 0.f;
	_offset = 0.f;
	animaiton_Count = 0;

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.f / 8.f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.f / 8.f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.f / 8.f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.f, 0.0f);

	pMesh = AEGfxMeshEnd();

	pTex[IDLE] = AEGfxTextureLoad("Assets/idle_right_down.png");
	pTex[WALK] = AEGfxTextureLoad("Assets/walk_right_down.png");
	pTex[JUMP] = AEGfxTextureLoad("Assets/Jump_Right_Down.png");
	pTex[DEATH] = AEGfxTextureLoad("Assets/death_normal_right_down.png");

	current_Character_State = IDLE;

	isFacingRight = true;
}

void Character::Update_Character()
{
	f64 dt = AEFrameRateControllerGetFrameTime();

	animation_Time += dt;

	if (animation_Time > 0.1)
	{
		animation_Time = 0;

		if (current_Character_State == DEATH && animaiton_Count > 6)
			animaiton_Count = 6;

		animaiton_Count = (animaiton_Count + 1) % animaiton_Total_Count;
	}

	Change_Character_State();

	if (current_Character_State != DEATH)
	{
		PlayerWalk(dt);
		//PlayerJump(dt);
	}

	PlayerDeath(dt);

	std::cout << current_Character_State << std::endl;

	Print_Character();
	
}

void Character::Exit_Character()
{
	AEGfxMeshFree(pMesh);
	pMesh = nullptr;

	for (int i = 0; i < MAX_CNT; i++)
	{
		if (pTex[i])
		{
			AEGfxTextureUnload(pTex[i]);
			pTex[i] = nullptr;
		}
	}
}

void Character::Print_Character()
{
	_offset = animaiton_Count * (1.f / 8.f);

	AEGfxSetBackgroundColor(0.5, 0.5, 0.5);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex[current_Character_State], _offset, 0);

	if(isFacingRight)
		Draw_Shape(_x, _y, _width, _height, 0.f, 0.f, 0.f, 1.f, pMesh, transform, true);
	else if(!isFacingRight)
		Draw_Shape(_x, _y, -_width, _height, 0.f, 0.f, 0.f, 1.f, pMesh, transform, true);
}

void Character::Change_Character_State()
{
	if (current_Character_State != DEATH)
	{
		if (current_Character_State == IDLE && AEInputCheckCurr(AEVK_D))
		{
			current_Character_State = WALK;
			animaiton_Count = 0;
			isFacingRight = true;
		}

		if (current_Character_State == IDLE && AEInputCheckCurr(AEVK_A))
		{
			current_Character_State = WALK;
			animaiton_Count = 0;
			isFacingRight = false;
		}

		if (current_Character_State != JUMP && (AEInputCheckReleased(AEVK_D) || AEInputCheckReleased(AEVK_A)))
		{
			current_Character_State = IDLE;
			animaiton_Count = 0;
		}

		if (AEInputCheckCurr(AEVK_SPACE))
		{
			current_Character_State = JUMP;
			animaiton_Count = 0;
		}

		if (current_Character_State == JUMP && animaiton_Count == 7)
		{
			current_Character_State = IDLE;
			animaiton_Count = 0;
		}

		if (AEInputCheckCurr(AEVK_K))
		{
			current_Character_State = DEATH;
			animaiton_Count = 0;
		}
	}
}

void Character::PlayerWalk(f64 dt)
{
	if (AEInputCheckCurr(AEVK_D))
	{
		_x += 50 * dt;
	}

	if (AEInputCheckCurr(AEVK_A))
	{
		_x -= 50 * dt;
	}
}

void Character::PlayerDeath(f64 dt)
{
	static f64 deathElapsedTime = 0;

	deathElapsedTime += dt;

	if (deathElapsedTime >= 5)
	{
		current_Character_State = IDLE;
		deathElapsedTime = 0;
		animaiton_Count = 0;
	}
}