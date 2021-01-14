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
	double FreezeThresh = 5000;
	double CurrentThresh = 0;
public:

	void SetHealth(double h);
	void SetOriginalHealth(double h);
	double GetHealth() const;

	void SetPower(int h);
	int GetPower() const;

	void SetAtkPerTurn(int h);
	int GetAtkPerTurn() const;


	void SetisCastleFrosted(bool b);
	bool GetisCastleFrosted() const;
	//bool GetHasCastleWon() const;
	//
	// TODO: Add More Member Functions As Needed
	//

	void AttackActive(PQueue<Enemy*>& FighterList, Stack<Enemy*>& HealerList, Queue<Enemy*>& FreezerList, int fightercount, int healercount, int freezercount);
	void CalculateTurnToFreeze();
	void DealDamage(Enemy*); //Responsible for damaging or freezing enemies
	void SetFreezeind(int f); //Freeze indicator equals 1 if the castle is frozen
	int GetFreezeind(); 
	void SetCurrentThresh(double c); 
	double GetCurrentThresh(); //Current freezing threshold

};

