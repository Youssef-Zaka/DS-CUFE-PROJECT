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



void Castle::AttackActive(PQueue<Enemy*>& FighterList, Stack<Enemy*>& HealerList, Queue<Enemy*>& FreezerList, int fightercount, int healercount, int freezercount,int timestep)
{
	CalculateTurnToFreeze();		
	//Some temporary Queus and stacks used in the dealing damage process
	PQueue<Enemy*> TempFighterList;
	Stack<Enemy*> TempHealerList;
	Queue<Enemy*> TempFreezerList;
	Enemy* Ep;
	int WhileTemp = 0;
	int HealerRemain = 0;
	int FreezerRemain = 0;
	while (FighterList.dequeue(Ep))
	{
		TempFighterList.enqueue(Ep, Ep->GetPriority());	//fill temporary fighter list with original fighter lsit
	}
	if (fightercount>= NumAtkPerTurn)
	{
		WhileTemp = NumAtkPerTurn;		//a temp used in while loop
	}
	else
	{
		HealerRemain = NumAtkPerTurn - fightercount;
		WhileTemp = fightercount;					//calculated reamining castle attacks after hitting fighters
	}
	while (WhileTemp)			//deal damage to fighters and return all back to fighter list
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
	if (HealerRemain)		//if there is still N remaining, hit healers
	{
		if (healercount < HealerRemain)		//calculate remaining healer hits, and if there was freezer hits
		{
			FreezerRemain = HealerRemain - healercount;
			HealerRemain = healercount;
		}
		while (HealerRemain)			//pop healer, hit him, then pop him in temp stack
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
		while (!HealerList.isEmpty())			//continue with remaining not hit healers if any
		{
			Ep = HealerList.peek();
			HealerList.pop();
			TempHealerList.push(Ep);
		}

		while (!TempHealerList.isEmpty())//pop back from temp to main again, retaining order
		{	
			Ep = TempHealerList.peek();
			TempHealerList.pop();
			HealerList.push(Ep);
		}
	}
	if (FreezerRemain)		//check if N not exhausted yet, hit freezers
	{
		while (FreezerList.dequeue(Ep))		//dequeu to temp
		{
			TempFreezerList.enqueue(Ep);
		}
		if (freezercount<FreezerRemain)
		{
			FreezerRemain = freezercount;
		}
		while (FreezerRemain)		//deal damage 
		{
			TempFreezerList.dequeue(Ep);
			DealDamage(Ep,timestep);
			FreezerList.enqueue(Ep);
			FreezerRemain--;
		}
		while (TempFreezerList.dequeue(Ep))		//return back to original list
		{
			FreezerList.enqueue(Ep);
		}
	}
}

void Castle::CalculateTurnToFreeze()	//Randomizes freeze turn with 20% probability
{
	int Random = rand() % 6;
	TurnToFreeze = Random;
	TurnToFreeze = !TurnToFreeze;
}

void Castle::DealDamage(Enemy* Ep, int timestep) //utility function used to deal damage, or freeze enemies 
{
	if (TurnToFreeze)		//if turn to freeze
	{
		if (Ep->GetFreezeDuration() >0)		//if already frozen return
		{
			return;
		}
		double poweroverdistance = (double)CastlePower/Ep->GetDistance();
		double Healthpercent = OriginalHealth / Health;
		int random = rand() % 16;
		int freezeDuration = poweroverdistance * Healthpercent * random;	//calculate freeze duration, some random elements are used to simulate weather conditions
		if (Ep->GetDistance() < 10)
		{
			int r = rand()%10;
			freezeDuration-= r;		
		}
		if (freezeDuration == 0)		//if calculated duration is 0, return
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
	double DamageDealt =(double)((double)CastlePower / Ep->GetDistance()) * (1/K);	//deal damage, decrememnt health by calculated amount
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

void Castle::SetFreezeind(int f)
{
	Freezeind = f;
}

int Castle::GetFreezeind()
{
	return Freezeind;
}

void Castle::SetCurrentThresh(double c)
{
	CurrentThresh = c;
	if (CurrentThresh >= FreezeThresh)
	{
		Freezeind = 1; // The castle is frozen
		CurrentThresh = 0; //The enemy freezer has no effect on the castle while it is frozen
	}

}

double Castle::GetCurrentThresh() //Get the current freezing threshold
{
	return CurrentThresh;
}
