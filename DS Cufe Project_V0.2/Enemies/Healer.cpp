#include "Healer.h"

Healer::Healer(int id, int T, int ArvT, double H, double P, int RP, double S) :
	Enemy(id, T, ArvT, H, P, RP, S)
{

}

void Healer::Move()
{
	if (Health < OriginalHealth / 2)
	{
		if (MovingBack == false)
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
	else
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

void Healer::Act()
{
}
