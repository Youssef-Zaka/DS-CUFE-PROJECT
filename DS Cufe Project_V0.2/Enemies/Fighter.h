#pragma once
#include "Enemy.h"

////ZAKA CREATED THIS//


class Fighter :
	public Enemy
{
public:
	Fighter(int id, int T, int ArvT, double H, double P, int RP, double S);

	void Move();
	void Act(Castle*);
};


