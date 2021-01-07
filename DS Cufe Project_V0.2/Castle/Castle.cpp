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

void Castle::AttackActive(PQueue<Enemy*>& FighterList, Stack<Enemy*>& HealerList, Queue<Enemy*>& FreezerList,PQueue<Enemy*>& FrozenList, int fightercount, int healercount, int freezercount)
{
	CalculateTurnToFreeze();
	if (TurnToFreeze)
	{
		FreezeEnemies(FighterList, HealerList,FreezerList ,FrozenList);
		return;
	}

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
		DealDamage(Ep);
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
			DealDamage(Ep);
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
			DealDamage(Ep);
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

void Castle::FreezeEnemies(PQueue<Enemy*>& FighterList, Stack<Enemy*>& HealerList, Queue<Enemy*>& FreezerList, PQueue<Enemy*>& FrozenList)
{

}

void Castle::DealDamage(Enemy* Ep)
{
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
	
}
