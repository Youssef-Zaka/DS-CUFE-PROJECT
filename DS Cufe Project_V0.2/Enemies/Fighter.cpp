#include "Fighter.h"
#include "..\Castle\Castle.h"

Fighter::Fighter(int id, int T, int ArvT, double H, double P, int RP, double S):
	Enemy(id,T,ArvT,H,P,RP,S)
{

}

void Fighter::Move()
{
	if (Health < OriginalHealth/2)//if below half health, move at half speed
	{
		for (int i = 0; i < Speed/2; i++)
		{
			DecrementDist();
		}
	}
	else
	{
		for (int i = 0; i < Speed; i++)	//else, move at regular speed
		{
			DecrementDist();
		}
	}

}

void Fighter::Act(Castle* CastleP, Queue<Enemy*>&, int activecount)
{
	double DamageDealt;				//Damage dealt variable placeholder
	double K = 1;
	if (Health <= (OriginalHealth/2))	//set K to 0.5 if below half health, 1 otherwise
	{
		K = 0.5;
	}

	DamageDealt = (K / Distance) * Power;		//calculations from document provided equation
	CastleP->SetHealth(CastleP->GetHealth() - DamageDealt);	//deal calculated damage
	if (CastleP->GetHealth() <  0)
	{
		CastleP->SetHealth(0);					//If below 0, reset to 0, is killed
	}
	return;
}
