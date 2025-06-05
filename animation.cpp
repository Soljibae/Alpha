#include "utils.hpp"
#include "animation.hpp"
#include "character.hpp"

Animation::Animation(): current_Animation_State(START){}

void Animation::Init_Animation()
{
	player.Init_Character();

	current_Animation_State = START;
}

void Animation::Update_Animation()
{
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		current_Animation_State = GAME_OVER;

	player.Update_Character();
}

void Animation::Exit_Animation()
{
	player.Exit_Character();
}

Animation::eAnimationState Animation::Get_Current_Animation_State()
{
	return current_Animation_State;
}