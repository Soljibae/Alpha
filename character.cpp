#include "character.hpp"
#include "utils.hpp"

Character::Character()
	: current_Character_State(IDLE)
	, pTex(AEGfxTextureLoad("Assets/idle_right_down.png"))
	, pMesh(0)
	, transform{0}
	, _x(0.f)
	, _y(0.f)
	, _width(384.f / 4.f)
	, _height(64.f * 2.f)
	, _offset(0.f)
	, animation_Time(0.f)
	, animaiton_Count(0)
{
}

Character::~Character()
{
	if (pMesh)
		AEGfxMeshFree(pMesh);
	if (pTex)
		AEGfxTextureUnload(pTex);
}

void Character::Init_Character()
{
	if (pMesh)
		AEGfxMeshFree(pMesh);
	if (pTex)
		AEGfxTextureUnload(pTex);

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

	pTex = AEGfxTextureLoad("Assets/idle_right_down.png");

	current_Character_State = IDLE;

}

void Character::Update_Character()
{
	f64 dt = AEFrameRateControllerGetFrameTime();

	animation_Time += dt;

	if (animation_Time > 0.1)
	{
		animation_Time = 0;
		animaiton_Count = (animaiton_Count + 1) % animaiton_Total_Count;

		_offset = animaiton_Count * (1.f / 8.f);
	}

	AEGfxSetBackgroundColor(0.5, 0.5, 0.5);

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	AEGfxTextureSet(pTex, _offset, 0);

	Draw_Shape(_x, _y, _width, _height, 0.f, 0.f, 0.f, 1.f, pMesh, transform, true);
}

void Character::Exit_Character()
{
	AEGfxMeshFree(pMesh);
	pMesh = nullptr;

	AEGfxTextureUnload(pTex);
	pTex = nullptr;
}