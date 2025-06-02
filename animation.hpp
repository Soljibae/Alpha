#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "AEEngine.h"
#include "utils.hpp"
#include "character.hpp"

class Animation
{
public:
	Animation();

	typedef enum
	{
		START,
		GAME_OVER
	} eAnimationState;

	void Init_Animation();
	void Update_Animation();
	void Exit_Animation();

	eAnimationState Get_Current_Animation_State();
private:
	eAnimationState current_Animation_State;
	Character player;
};

#endif