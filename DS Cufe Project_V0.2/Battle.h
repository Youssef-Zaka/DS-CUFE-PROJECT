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
	void AddtoActiveList(Enemy* Ptr);		//Adds an enemy to active list, increment active count
	void AddtoFightersList(Enemy* Ptr);		//Add to fighter list, increment fighter count 
	void AddtoHealersList(Enemy* Ptr);		//add to healers list increment healer count 
	void AddtoFreezersList(Enemy* Ptr);		//add to freezer list incrememnt freezer count
	void AddtoFrostedList(Enemy* Ptr);		//add to frosted list increment frosted count
	void AddtoKilledList(Enemy* Ptr);		//add to killed list incrememnt killed count 
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	void UpdateEnemies();					//move and apply enemy acttions one by one if not frosted 
	void ProcessFrostedList();				//Check for killed in Frosted list
	void PrepareListsP_Q_S();				//ReEnqueue Enemey lists with new priorities or STATUS
	void EmptyFighterList();				//Prepare Fighter list , used in Above Function
	void EmptyHealerList();					//Prepare Healer list , used in Above Function
	void EmptyFreezerList();				//Prepare Freezer list , used in Above Function
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Silent_Mode();						//Silent mode Loop, NO drawing, just output file
	void Step_By_Step_Mode();				//Step by step mode Loop, update each second
	void InterActive_Mode();				//Interactive mode Loop, update each click
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	void PrepareActiveList();				//Check active list for Status ailments or deaths
	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	string SetformatOutput(int);			//Format for output file

};

