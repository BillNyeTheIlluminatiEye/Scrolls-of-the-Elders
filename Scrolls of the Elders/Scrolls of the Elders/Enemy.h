#pragma once
#include "Character.h"
class Enemy:Character
{
public:

	Enemy();
	~Enemy();
	void attackSFML(); //Actuator and Animation for Attack (Sword)
	void attack(Character target); //Attack Function (Sword)
};

