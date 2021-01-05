#include "Battle.h"
#include <time.h>

Battle::Battle()
{	
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}
void Battle::AddtoActiveList(Enemy* Ptr)
{
	Q_Active.enqueue(Ptr);
	ActiveCount++;
}
void Battle::AddtoFightersList(Enemy* Ptr)
{
	Q_Fighters.enqueue(Ptr);
	FighterCount++;
}
void Battle::AddtoHealersList(Enemy* Ptr)
{
	S_Healers.push(Ptr);
	HealerCount++;
}void Battle::AddtoFreezersList(Enemy* Ptr)
{
	Q_Freezers.enqueue(Ptr);
	FreezerCount++;
}
void Battle::AddtoFrostedList(Enemy* Ptr)
{
	Q_Frosted_List.enqueue(Ptr);
	FrostedCount++;
}
void Battle::AddtoKilledList(Enemy* Ptr)
{
	Q_Killed_List.enqueue(Ptr);
	KilledCount++;
}

Castle * Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InterActive_Mode();
		break;
	case MODE_STEP:
		Step_By_Step_Mode();
		break;
	case MODE_SLNT:
		Silent_Mode();
		break;
	case MODE_DEMO:
		Just_A_Demo();

	}

	delete pGUI;
	
}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{	
//	
//	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
//	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer
//
//	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
//	pGUI->waitForClick();
//
//	CurrentTimeStep = 0;
//	//
//	// THIS IS JUST A DEMO Function
//	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
//	//
//	 
//	srand(time(NULL));
//	int Enemy_id = 0;
//	int ArrivalTime=1;
//	Enemy* pE= NULL;
//	//Create Random enemies and add them all to inactive queue
//	for(int i=0; i<EnemyCount; i++)
//	{			
//		ArrivalTime += (rand()%3);	//Randomize arrival time
//		pE = new Enemy(++Enemy_id,ArrivalTime);
//		pE->SetStatus( INAC); //initiall all enemies are inactive
//		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
//	}	
//
//	AddAllListsToDrawingList();
//	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive
//
//	pGUI->waitForClick();
//	
//	while( KilledCount < EnemyCount )	//as long as some enemies are alive (should be updated in next phases)
//	{
//		CurrentTimeStep++;
//		ActivateEnemies();    
//
//		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)
//
//		pGUI->ResetDrawingList();
//		AddAllListsToDrawingList();
//		pGUI->UpdateInterface(CurrentTimeStep);
//		Sleep(250);
//	}		
}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{	
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const * EnemyList = Q_Inactive.toArray(InactiveCount);
	for(int i=0; i<InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList

	int ActiveC = 0; //Variable to be passed by reference to toArray function, it stores queue size
	for(int i=0; i<ActiveCount; i++)
		pGUI->AddToDrawingList(Q_Active.toArray(ActiveC)[i]); //Adds ActiveList to DrawingList
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy *pE;
	while( Q_Inactive.peekFront(pE) )	//as long as there are more inactive enemies
	{
		if(pE->GetArrvTime() > CurrentTimeStep )	//no more arrivals at current time
			return;
				
		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		AddtoActiveList(pE);
		if (pE->GetType() == 0)
		{
			AddtoFightersList(pE);
		}
		else if (pE->GetType() == 1)
		{
			AddtoHealersList(pE);
		}
		else if (pE->GetType() == 2)
		{
			AddtoFreezersList(pE);
		}
	
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()	
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;	
	srand(time(0));
	for(int i=0; i<DemoListCount; i++)
	{
		pE = DemoList[i];
		switch(pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand()%100;
			if(Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST); 
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp+KillProp) )	//with kill propablity, kill some active enemies
					{
						pE->SetStatus(KILD);	
						ActiveCount--;
						KilledCount++;
					}
			
			break;
		case FRST:
			Prop = rand()%100;
			if(Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp+KillProp) )			//with kill propablity, kill some frosted enemies
					{
						pE->SetStatus(KILD);	
						FrostedCount--;
						KilledCount++;
					}

			break;
		}
	}
}
void Battle::UpdateEnemies() 
{	
	Enemy* Ep;
	for (int i = 0; i < ActiveCount; i++)
	{
		Q_Active.dequeue(Ep);
		Ep->Move();
		Q_Active.enqueue(Ep);
	}
}

void Battle::Silent_Mode()
{
	CurrentTimeStep = 0;
}

void Battle::Step_By_Step_Mode()
{
	CurrentTimeStep = 0; //reset time step 
	getinput();			//Get Input from file
	AddAllListsToDrawingList();	
	pGUI->UpdateInterface(CurrentTimeStep, 0, 0, 0, 0, 0, 0, 0, 00, 0, 0, 0,0,0,0);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
	CurrentTimeStep++;
	ActivateEnemies();
	UpdateEnemies();
	pGUI->ResetDrawingList();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep,0,0,0,0,0,0,0,00,0,0,0,0,0,0);
	//pGUI->waitForClick(); //THis is step by step, so we wait for one second
	Sleep(100);
	}
}

void Battle::InterActive_Mode()
{
	CurrentTimeStep = 0; //reset time step 
	getinput();			//Get Input from file
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, GetCastle()->GetHealth(),GetCastle()->GetisCastleFrosted(),
						  0,0,0,0,0,0,0,0,0,0,0,0);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		UpdateEnemies();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep, 0, 0, 0, 0, 0, 0, 0, 00, 0, 0, 0,0,0,0);
		pGUI->waitForClick(); //THis is Interactive, so we wait for click
		/*Sleep(100);*/
	}
}

void Battle::Update_Enemies()
{
}


//Kareem
//Get input function that takes in the parameters of the game mode from input file
void Battle::getinput()
{
	fstream file("input.txt");
	double ch;
	int n, cp;
	file >> ch;
	file >> n;
	file >> cp;
	BCastle.SetHealth(ch);
	BCastle.SetAtkPerTurn(n);
	BCastle.SetPower(cp);
	int count;
	file >> count;
	EnemyCount = count;
	int id, Type, AT, RLD;
	double H, SPD,POW;
	Enemy* eptr=NULL;
	for (int i = 0; i < count; i++)
	{
		file >> id;
		file >> Type;
		file >> AT;
		file >> H;
		file >> POW;
		file >> RLD;
		file >> SPD;

		if (Type == 0)
		{
			eptr = new Fighter(id, Type, AT, H, POW, RLD, SPD);
		}
		else if (Type == 1)
		{
			eptr = new Healer(id, Type, AT, H, POW, RLD, SPD);
		}
		else
		{
			eptr = new Freezer(id, Type, AT, H, POW, RLD, SPD);
		}
		eptr->SetStatus(INAC);
		Q_Inactive.enqueue(eptr);
	}
}