#include "Castle.h"




void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}

void Castle::SetPower(int p)
{
	if (p > 0)
		CastlePower = p;
}

void Castle::SetAtkPerTurn(int a)
{
	if (a > 0)
		NumAtkPerTurn = a;
}

int Castle::GetPower() const
{
	return CastlePower;
}

int Castle::GetAtkPerTurn() const
{
	return NumAtkPerTurn;
}