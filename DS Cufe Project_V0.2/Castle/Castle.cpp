#include "Castle.h"




void Castle::SetHealth(double h)
{
	if(h > 0)
		Health = h;
	else
		Health = 0; // killed
}

void Castle::SetOriginalHealth(double h)
{
	OriginalHealth = h;
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

void Castle::SetisCastleFrosted(bool b)
{
	isCastleFrosted = b;
}

bool Castle::GetisCastleFrosted() const
{
	return isCastleFrosted;
}

//bool Castle::GetHasCastleWon() const
//{
//	return HasCastleWon;
//}

void Castle::AttackActive(PQueue<Enemy*>& FighterList, Stack<Enemy*>& HealerList, Queue<Enemy*>& FreezerList, int fightercount, int healercount, int freezercount,int timestep)
{
	CalculateTurnToFreeze();
	PQueue<Enemy*> TempFighterList;
	Stack<Enemy*> TempHealerList;
	Queue<Enemy*> TempFreezerList;
	Enemy* Ep;
	int WhileTemp = 0;
	int HealerRemain = 0;
	int FreezerRemain = 0;
	while (FighterList.dequeue(Ep))
	{
		TempFighterList.enqueue(Ep, Ep->GetPriority());
	}
	if (fightercount>= NumAtkPerTurn)
	{
		WhileTemp = NumAtkPerTurn;
	}
	else
	{
		HealerRemain = NumAtkPerTurn - fightercount;
		WhileTemp = fightercount;
	}
	while (WhileTemp)
	{
		TempFighterList.dequeue(Ep);
		DealDamage(Ep,timestep);
		FighterList.enqueue(Ep, Ep->GetPriority());	
		WhileTemp--;
	}
	while (TempFighterList.dequeue(Ep))
	{
		FighterList.enqueue(Ep, Ep->GetPriority());
	}
	if (HealerRemain)
	{
		if (healercount < HealerRemain)
		{
			FreezerRemain = HealerRemain - healercount;
			HealerRemain = healercount;
		}
		while (HealerRemain)
		{
			Ep = HealerList.peek();
			HealerList.pop();
			DealDamage(Ep,timestep);
			if (Ep->GetHealth() <= 0)
			{
				if (Ep->GetDistance() <= 5)
				{
					Health += (0.03*OriginalHealth);
					if (Health > OriginalHealth)
					{
						Health = OriginalHealth;
					}
				}
			}
			TempHealerList.push(Ep);
			HealerRemain--;
		}
		while (!HealerList.isEmpty())
		{
			Ep = HealerList.peek();
			HealerList.pop();
			TempHealerList.push(Ep);
		}

		while (!TempHealerList.isEmpty())
		{	
			Ep = TempHealerList.peek();
			TempHealerList.pop();
			HealerList.push(Ep);
		}
	}
	if (FreezerRemain)
	{
		while (FreezerList.dequeue(Ep))
		{
			TempFreezerList.enqueue(Ep);
		}
		if (freezercount<FreezerRemain)
		{
			FreezerRemain = freezercount;
		}
		while (FreezerRemain)
		{
			TempFreezerList.dequeue(Ep);
			DealDamage(Ep,timestep);
			FreezerList.enqueue(Ep);
			FreezerRemain--;
		}
		while (TempFreezerList.dequeue(Ep))
		{
			FreezerList.enqueue(Ep);
		}
	}
}

void Castle::CalculateTurnToFreeze()
{
	int Random = rand() % 6;
	TurnToFreeze = Random;
	TurnToFreeze = !TurnToFreeze;
}

void Castle::DealDamage(Enemy* Ep, int timestep)
{
	if (TurnToFreeze)
	{
		if (Ep->GetFreezeDuration() >0)
		{
			return;
		}
		double poweroverdistance = (double)CastlePower/Ep->GetDistance();
		double Healthpercent = OriginalHealth / Health;
		int random = rand() % 16;
		int freezeDuration = poweroverdistance * Healthpercent * random;
		if (Ep->GetDistance() < 10)
		{
			int r = rand()%10;
			freezeDuration-= r;
		}
		if (freezeDuration == 0)
		{
			return;
		}
		Ep->SetFreezeDuration(freezeDuration);
		if (Ep->GetFSTS() > timestep)
		{
			Ep->SetFSTS(timestep);
		}
		return;
	}
	double K;
	if (Ep->GetType() == 1)
	{
		K = 2;
	}
	else
	{
		K = 1;
	}
	double DamageDealt =(double)((double)CastlePower / Ep->GetDistance()) * (1/K);
	Ep->SetHealth(Ep->GetHealth() - DamageDealt);
	if (Ep->GetFSTS() > timestep)
	{
		Ep->SetFSTS(timestep);
	}
	return;
}

double Castle::GetOriginalHealth()
{
	return OriginalHealth;
}