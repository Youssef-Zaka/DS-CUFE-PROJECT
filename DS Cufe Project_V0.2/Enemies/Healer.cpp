#include "Healer.h"

Healer::Healer(int id, int T, int ArvT, double H, double P, int RP, double S) :
	Enemy(id, T, ArvT, H, P, RP, S)
{

}

void Healer::Move()
{
	if (Health < OriginalHealth / 2)		//if half health or lower, then half speed
	{
		if (MovingBack == false)			//check which direction he is moving in
		{
			if (Distance - Speed/2 >= MinDistance)
			{
				for (int i = 0; i < Speed/2; i++)
				{
					DecrementDist();
				}
			}
			else if (Distance - Speed/2 < MinDistance)
			{
				//Move Forward Untill u cant any more, then move back
				for (int i = 0; i < Speed/2; i++)
				{
					if (Distance - 1 >= MinDistance) //loop to decrement distance by speed
					{
						if (!MovingBack)
						{
							DecrementDist();
							continue;
						}
					}
					MovingBack = true;
					if (MovingBack)
					{
						IncrementDist();
					}
				}
			}
		}
		else
		{
			if (MovingBack)
			{
				if (Distance + Speed/2 <= MaxDistance)
				{
					for (int i = 0; i < Speed/2; i++)
					{
						IncrementDist();
					}
				}
				else if (Distance + Speed/2 > MaxDistance)
				{
					//Move Forward Untill u cant any more, then move back
					for (int i = 0; i < Speed/2; i++)
					{
						if (Distance + 1 <= MinDistance)
						{
							if (MovingBack)
							{
								IncrementDist();
								continue;
							}
						}
						MovingBack = false;
						if (!MovingBack)
						{
							DecrementDist();
						}
					}
				}
			}
		}

	}
	else // if above half health do the same but at regular speed
	{
		if (MovingBack == false)
		{
			if (Distance - Speed >= MinDistance)
			{
				for (int i = 0; i < Speed; i++)
				{
					DecrementDist();
				}
			}
			else if (Distance - Speed < MinDistance)
			{
				//Move Forward Untill u cant any more, then move back
				for (int i = 0; i < Speed; i++)
				{	
					if (Distance - 1 >= MinDistance)
					{	
						if (!MovingBack)
						{
							DecrementDist();
							continue;
						}
					}
					MovingBack = true;
					if (MovingBack)
					{	
						IncrementDist();
					}
				}
			}
		}
		else
		{
			if (MovingBack)
			{
				if (Distance + Speed <= MaxDistance)
				{
					for (int i = 0; i < Speed; i++)
					{
						IncrementDist();
					}
				}
				else if (Distance + Speed > MaxDistance)
				{
					//Move Forward Untill u cant any more, then move back
					for (int i = 0; i < Speed; i++)
					{
						if (Distance + 1 <= MinDistance)
						{
							if (MovingBack)
							{
								IncrementDist();
								continue;
							}
						}
						MovingBack = false;
						if (!MovingBack)
						{
							DecrementDist();
						}
					}
				}
			}
		}
	}	
}

void Healer::Act(Castle*, Queue<Enemy*>& Active, int activecount)
{
	double HealedValue;			//Healing value placeholder
	double HealerValues = (Health/OriginalHealth) * Power;
	Enemy* Ep;
	for (int i = 0; i < activecount-1; i++)
	{
		Active.dequeue(Ep);
		double EnemyValues = Ep->GetHealth()/Ep->GetOriginalHealth();
		double DistanceDoniminator = (1.0 + abs(Ep->GetDistance() - Distance));
		double DistanceValues = 1 / DistanceDoniminator;
		HealedValue = (HealerValues *EnemyValues) * DistanceValues ;	//Calculated healing value from previous sub values
		if (MovingBack)		//if moving back, heal enemies with greater distance but not greater than 2
		{
			if (Ep->GetDistance() >= Distance && Ep->GetDistance() <= (Distance + 2))
			{
				Ep->SetHealth(Ep->GetHealth() + HealedValue);
				if (Ep->GetHealth() > Ep->GetOriginalHealth())
				{
					Ep->SetHealth(Ep->GetOriginalHealth());
				}
			}
		}
		else
		{	//if moving forward, heal enemies with smaller distance but not smaller than 2
			if (Ep->GetDistance() >= (Distance-2 )&& Ep->GetDistance() <= (Distance))
			{
				Ep->SetHealth(Ep->GetHealth() + HealedValue);
				if (Ep->GetHealth() > Ep->GetOriginalHealth())
				{
					Ep->SetHealth(Ep->GetOriginalHealth());
				}
			}
		}
		Active.enqueue(Ep);	//return Enemy back to active list
	}

}
