#pragma once

#include "Enemies\Enemy.h"
#include "Enemies\Fighter.h"
#include "Enemies\Freezer.h"
#include "Enemies\Healer.h"
#include "Castle\Castle.h"
#include "Generic_DS\Queue.h"
#include "GUI\GUI.h"
#include "Generic_DS/Stack.h"
#include "Generic_DS/PQueue.h"
#include <fstream>

// it is the controller of the project
class Battle
{////////////////////////////////////////////////////////////////////////////////////////////////
private:
	GUI* pGUI;														//Pointer to GUI
	Castle BCastle;													//Castle Object
	int EnemyCount;													//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;						//no. of enemies (Active, Frosted, killed so far)
	int FighterCount, HealerCount, FreezerCount;
	int FrozenFighterCount, FrozenHealerCount, FrozenFreezerCount;
	int KilledFighterCount, KilledHealerCount, KilledFreezerCount;
	int CurrentTimeStep;											//current simulation time step
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	Queue<Enemy*> Q_Inactive;										//Queue of inactive enemies
	Queue<Enemy*> Q_Active;											//Queue of active enemies
	PQueue<Enemy*> Q_Fighters;										//Priority fighters Queue
	PQueue<Enemy*> Q_Frosted_List;									//Priority Frosted Queue
	Stack<Enemy*> S_Healers;										//Stack if healers
	Queue<Enemy*> Q_Freezers;										//Queue of freezers
	Queue<Enemy*> Q_Killed_List;									//queue of killed enemies
	////////////////////////////////////////////////////////////////////////////////////////////////
	//IsGameWin
	// TODO: Add More Data Members As Needed
	bool IsGameWin = false;  //True if castle killed all 
	bool IsGameLoss = false; //True is castle died
	//
	////////////////////////////////////////////////////////////////////////////////////////////////
public:
	////////////////////////////////////////////////////////////////////////////////////////////////
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();					//Returns a pointer
	void RunSimulation();					//Start Simulation
	void ActivateEnemies();					//check the inactive list and activate all enemies that has arrived
	void getinput();						//Get Input from Input File
	void CreateOutput();					//Export Output To ouputfile
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////	
	void AddtoActiveList(Enemy* Ptr);
	void AddtoFightersList(Enemy* Ptr);
	void AddtoHealersList(Enemy* Ptr);
	void AddtoFreezersList(Enemy* Ptr);
	void AddtoFrostedList(Enemy* Ptr);
	void AddtoKilledList(Enemy* Ptr);

	void UpdateEnemies();

	void ProcessFrostedList();
	void PrepareListsP_Q_S();
	void EmptyFighterList();
	void EmptyHealerList();
	void EmptyFreezerList();
	//
	// TODO: Add More Member Functions As Needed
	//
	//ZAKA
	//Adding Functions for different game modes, silent, step by step and interactive
	void Silent_Mode();
	void Step_By_Step_Mode();
	void InterActive_Mode(); 
	
	///TODO UPDATE ACTIVE LIST WITH NEW DEATHS AND FREEZES EACH TURN
	void PrepareActiveList();

	string SetformatOutput(int);

};

