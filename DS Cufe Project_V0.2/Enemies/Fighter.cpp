#include "Fighter.h"
#include "..\Castle\Castle.h"

Fighter::Fighter(int id, int T, int ArvT, double H, double P, int RP, double S):
	Enemy(id,T,ArvT,H,P,RP,S)
{

}

void Fighter::Move()
{
	if (Health < OriginalHealth/2)
	{
		for (int i = 0; i < Speed/2; i++)
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

void Fighter::Act(Castle* CastleP, Queue<Enemy*>&, int activecount)
{
	double DamageDealt;
	double K = 1;
	if (Health <= (OriginalHealth/2))
	{
		K = 0.5;
	}

	DamageDealt = (K / Distance) * Power;
	CastleP->SetHealth(CastleP->GetHealth() - DamageDealt);
	if (CastleP->GetHealth() <  0)
	{
		CastleP->SetHealth(0);
	}
	return;
}
