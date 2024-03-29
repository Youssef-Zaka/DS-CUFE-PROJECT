#include "Enemy.h"


Enemy::Enemy(int id, int arrTime, int d):ID(id),ArrvTime(arrTime),OriginalHealth(Health)
{
	SetDistance(d);
}

Enemy::Enemy(int id,int T, int ArvT, double H, double P, int RP, double S):ID(id),ArrvTime(ArvT),
Health(H),Power(P),ReloadPeriod(RP),Speed(S),Type(T),OriginalHealth(H)
{
	SetStatus(INAC);
	SetDistance(MaxDistance);
	CurrentReload = 0;
}

Enemy::~Enemy()
{
}

int Enemy::GetID() const
{
	return ID;
}

int Enemy::GetType() const
{
	return Type;
}


void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::IncrementDist()  //Used With Healers as they go back an forth
{
	if (Distance < MaxDistance)
		Distance++;
}


void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Enemy::GetDistance() const
{
	return Distance;
}

double Enemy::GetPriority() const
{
	double DPS = Power / ReloadPeriod;
	double HealthRatio = pow((OriginalHealth / Health), 2);;
	double PreFrozenValues = (HealthRatio/Distance)*DPS;
	double FrozenFactor = 1 / (1+FreezePeriod);
	return PreFrozenValues * FrozenFactor;
}

void Enemy::SetFreezeDuration(int i)
{
	FreezeDuration = i;
}

int Enemy::GetFreezeDuration()
{
	return FreezeDuration;
}



int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

double Enemy::GetHealth() const
{
	return Health;
}

double Enemy::GetPower() const
{
	return Power;
}

int Enemy::GetReloadPeriod() const
{
	return ReloadPeriod;
}

double Enemy::GetSpeed() const
{
	return Speed;
}

double Enemy::GetOriginalHealth() const
{
	return OriginalHealth;
}

void Enemy::SetHealth(double H)
{
	Health = H;
}

void Enemy::SetPower(double P)
{
	Power = P;
}

void Enemy::SetSpeed(double S)
{
	Speed = S;
}

void Enemy::SetKTS(int x)
{
	KillTimeStep = x;
}

void Enemy::SetFSTS(int x)
{
	FirstshotTimeStep = x;
}

int Enemy::GetKTS()
{
	return KillTimeStep;
}

int Enemy::GetFSTS()
{
	return FirstshotTimeStep;
}

int Enemy::GetReloadCounter()
{
	return ReloadCounter;
}

void Enemy::SetReloadCounter(int rc)
{
	ReloadCounter = rc;
}






