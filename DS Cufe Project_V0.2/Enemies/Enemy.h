#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	//Input File Data Members////////////////////////////////////////////
	const int ID;        //Each enemy has a unique ID (sequence number)
	int Type;
	const int ArrvTime;	//arrival time (time it starts to join battle)
	double Health;	//Enemy health
	double Power;
	int ReloadPeriod;
	double Speed;
	//End of Input file member bits//////////////////////////////////////
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	

	int FreezePeriod = 0;//Member used in priority calculations and in Frosted Checks, default value = 0	
	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	//
	// TODO: Add More Data Members As Needed
	//
	const double OriginalHealth;
	int CurrentReload;
	int FreezeDuration;
public:
	Enemy(int id, int arrTime, int d = MaxDistance);
	Enemy(int id,int T, int ArvT, double H, double P, int RP, double S);
	virtual ~Enemy();
	//Getters and Setters///////////////////////ZAKA//
	int Enemy::GetID() const;
	int Enemy::GetType() const;
	int GetArrvTime() const;
	double Enemy::GetHealth()const;
	double Enemy::GetPower()const;
	int Enemy::GetReloadPeriod()const;
	double Enemy::GetSpeed()const;
	double Enemy::GetOriginalHealth()const;
	/////////////////////////////////////////////
	void Enemy::SetHealth(double);
	void Enemy::SetPower(double);
	void Enemy::SetSpeed(double);
	/////////////////////////////////////////////
	void DecrementDist();
	void IncrementDist();
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	void SetDistance(int );
	int GetDistance() const;
	/////////////////////////////////////////////	
	double GetPriority() const;
	void SetFreezeDuration(int i);
	int GetFreezeDuration();
	// Virtual Functions: ----------------

	virtual void Move() = 0;	//All enemies can move
	virtual void Act() = 0;	//Acting means fighting or healing

	//
	// TODO: Add More Member Functions As Needed
	//

};

