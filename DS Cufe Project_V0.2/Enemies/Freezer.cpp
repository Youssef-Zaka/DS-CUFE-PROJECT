#include "Freezer.h"
#include "..\Castle\Castle.h"
Freezer::Freezer(int id, int T, int ArvT, double H, double P, int RP, double S) :
	Enemy(id, T, ArvT, H, P, RP, S)
{

}

void Freezer::Move()
{
	if (Health < OriginalHealth / 2)		//if below half health, move at half speed
	{
		for (int i = 0; i < Speed / 2; i++)
		{
			DecrementDist();
		}
	}
	else
	{
		for (int i = 0; i < Speed; i++)		//else, move at regular speed
		{
			DecrementDist();
		}
	}
}

void Freezer::Act(Castle* c, Queue<Enemy*>&, int activecount)
{

	//Amount of ice a freezer can throw on a castle
	double IceAmount = (Power * (Health / OriginalHealth)) / (4.0 * Distance);

	if (c->GetFreezeind() == 1)//If the castle is frozen, the freezer has no effect on it
	{
		return;
	}
	c->SetCurrentThresh(c->GetCurrentThresh() + IceAmount); //Add the amount of ice thrown by the freezers
	if (c->GetFreezeind() == 1) //The castle is frozen
	{
		c->SetisCastleFrosted(true);
	}
	if (c->GetFreezeind() == 0 || c->GetFreezeind() == 2)
	{
		c->SetisCastleFrosted(false);
	}

}

