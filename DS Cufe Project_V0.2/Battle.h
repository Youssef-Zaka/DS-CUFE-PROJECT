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
{
private:
	GUI* pGUI;
	Castle BCastle;
	int EnemyCount;	//the actual number of enemies in the game
	int ActiveCount, FrostedCount, KilledCount;	//no. of enemies (Active, Frosted, killed so far)
	int FighterCount, HealerCount, FreezerCount;
	int FrozenFighterCount, FrozenHealerCount, FrozenFreezerCount;
	int KilledFighterCount, KilledHealerCount, KilledFreezerCount;
	int CurrentTimeStep;
	//Enemy * BEnemiesForDraw[MaxEnemyCount]; // This Array of Pointers is used for drawing elements in the GUI
								  			// No matter what list type you are using to hold enemies, 
											// you must pass the enemies to the GUI function as an array of enemy pointers. 
											// At every time step, you should update those pointers 
											// to point to the current active enemies 
											// then pass the pointers list to the GUI function

	Queue<Enemy*> Q_Inactive;		//Queue of inactive enemies
	Queue<Enemy*> Q_Active;		//Queue of active enemies

	PQueue<Enemy*> Q_Fighters; //Priority Queue
	PQueue<Enemy*> Q_Frosted_List; //Priority Queue
	Stack<Enemy*> S_Healers; //Stack if healers
	Queue<Enemy*> Q_Freezers; //Queue of freezers
	Queue<Enemy*> Q_Killed_List; //queue of killed enemies
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	//Queue for all enemies in the battle
	int DemoListCount;
	Enemy* DemoList[MaxEnemyCount];	//Important: This is just for demo
	/// ==>


	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Battle();
	void AddAllListsToDrawingList();		//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
	Castle * GetCastle();
	void RunSimulation();
	void ActivateEnemies();		//check the inactive list and activate all enemies that has arrived
	void getinput();

		
	void AddtoDemoList(Enemy* Ptr);		//Add Enemy to the demo queue of enemies (for demo purposes only)
	void AddtoActiveList(Enemy* Ptr);
	void AddtoFightersList(Enemy* Ptr);
	void AddtoHealersList(Enemy* Ptr);
	void AddtoFreezersList(Enemy* Ptr);
	void AddtoFrostedList(Enemy* Ptr);
	void AddtoKilledList(Enemy* Ptr);
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes)

	void UpdateEnemies();

	void PrepareFighterPQ();
	void PrepareHealerPQ();
	void PrepareFreezerrPQ();
	void PrepareFrozenPQ();
	void EmptyFighterList();
	void EmptyHealerList();
	void EmptyFreezerList();
	void EmptyFrozenList();
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

};

