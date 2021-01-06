#include "Freezer.h"

Freezer::Freezer(int id, int T, int ArvT, double H, double P, int RP, double S) :
	Enemy(id, T, ArvT, H, P, RP, S)
{

}

void Freezer::Move()
{
	if (Health < OriginalHealth / 2)
	{
		for (int i = 0; i < Speed / 2; i++)
		{
			DecrementDist();
		}
	}
	else
	{
		for (int i = 0; i < Speed; i++)
		{
			DecrementDist();
		}
	}
}

void Freezer::Act()
{
}

