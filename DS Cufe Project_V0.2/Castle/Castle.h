#pragma once
#include "..\Defs.h"
#include"..\Generic_DS\Queue.h"
#include "..\Generic_DS\PQueue.h"
#include "..\Generic_DS\Stack.h"
#include "..\Enemies\Enemy.h"
#include <time.h>
class Castle
{
	double Health;
	double OriginalHealth;
	//
	// TODO: Add More Data Members As Needed
	//
	//Members added by ZAKA//

	int NumAtkPerTurn; //ZAKA:: Number of enemies the castle may attack per turn, This value is retrieved from input file.
	int CastlePower; // Castle Power retrived from input file.

	bool isCastleFrosted = false;
	bool TurnToFreeze;
	//bool HasCastleWon = false;
	int Freezeind = 0;
	double FreezeThresh = 500;
	double CurrentThresh = 0;
public:
	//setters and getters
	void SetHealth(double h);
	void SetOriginalHealth(double h);
	double GetHealth() const;
	double GetOriginalHealth();

	void SetPower(int h);
	int GetPower() const;

	void SetAtkPerTurn(int h);
	int GetAtkPerTurn() const;


	void SetisCastleFrosted(bool b);
	bool GetisCastleFrosted() const;


	void AttackActive(PQueue<Enemy*>& FighterList, Stack<Enemy*>& HealerList, Queue<Enemy*>& FreezerList, int fightercount, int healercount, int freezercount, int timestep);
	void CalculateTurnToFreeze();
	void DealDamage(Enemy*,int); //Responsible for damaging or freezing enemies
	void SetFreezeind(int f); //Freeze indicator equals 1 if the castle is frozen
	int GetFreezeind();
	void SetCurrentThresh(double c);
	double GetCurrentThresh(); //Current freezing threshold
};

