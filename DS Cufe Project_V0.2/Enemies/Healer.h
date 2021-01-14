#pragma once
#include "Enemy.h" 

////ZAKA CREATED THIS//
class Healer :
	public Enemy
{
	bool MovingBack = 0;
public:
	Healer(int id, int T, int ArvT, double H, double P, int RP, double S);
	void Move();
	void Act(Castle*, Queue<Enemy*>&, int activecount);
};

