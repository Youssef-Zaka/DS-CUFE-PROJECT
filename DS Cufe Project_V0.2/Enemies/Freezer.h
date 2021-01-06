#pragma once
#include "Enemy.h"

////ZAKA CREATED THIS//
class Freezer :
	public Enemy
{
public:
	Freezer(int id, int T, int ArvT, double H, double P, int RP, double S);
	void Move();
	void Act();
};

