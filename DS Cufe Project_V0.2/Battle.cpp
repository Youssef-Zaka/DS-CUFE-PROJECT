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
	FighterCount = 0;
	FreezerCount = 0;
	HealerCount = 0;
	FrozenFighterCount = 0;
	FrozenHealerCount = 0;
	FrozenFreezerCount = 0;
	KilledFighterCount = 0;
	KilledHealerCount = 0;
	KilledFreezerCount = 0;
	srand(time(NULL)); //Every battle Instance Generates a new seed

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
	Q_Fighters.enqueue(Ptr,Ptr->GetPriority());
	FighterCount++;
}
void Battle::AddtoHealersList(Enemy* Ptr)
{
	S_Healers.push(Ptr);
	HealerCount++;
}
void Battle::AddtoFreezersList(Enemy* Ptr)
{
	Q_Freezers.enqueue(Ptr);
	FreezerCount++;
}
void Battle::AddtoFrostedList(Enemy* Ptr)
{
	Q_Frosted_List.enqueue(Ptr,Ptr->GetFreezeDuration());
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
	for (int i = 0; i < KilledCount; i++)
		pGUI->AddToDrawingList(Q_Killed_List.toArray(ActiveC)[i]); //Adds Killed to DrawingList
	for (int i = 0; i < FrostedCount; i++)
		pGUI->AddToDrawingList(Q_Frosted_List.toArray(ActiveC)[i]); //Adds Frosted to DrawingList
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
		if (!Ep->GetReloadCounter())
		{
			Ep->Act(GetCastle(), Q_Active,ActiveCount);
		}
		Ep->SetReloadCounter(Ep->GetReloadCounter()+1);
		if (Ep->GetReloadCounter() == Ep->GetReloadPeriod())
		{
			Ep->SetReloadCounter(0);
		}
		Q_Active.enqueue(Ep);
	}
}

void Battle::ProcessFrostedList()
{
	Enemy* Ep;
	int Freezeint = FrostedCount;
	while (Freezeint)
	{
		Freezeint--;
		Q_Frosted_List.dequeue(Ep);
		Ep->SetFreezeDuration(Ep->GetFreezeDuration()-1);
		if (Ep->GetFreezeDuration() <= 0)
		{
			Q_Active.enqueue(Ep);
			ActiveCount++;
			FrostedCount--;
			if (Ep->GetType() == 0)
			{
				FrozenFighterCount--;
			}
			else if (Ep->GetType() == 1)
			{
				FrozenHealerCount--;
			}
			else
			{
				FrozenFreezerCount--;
			}
			Ep->SetStatus(ACTV);
			continue;
		}
		Q_Frosted_List.enqueue(Ep,Ep->GetFreezeDuration());
	}
}

void Battle::PrepareListsP_Q_S()
{
	EmptyFighterList();
	EmptyFreezerList();
	EmptyHealerList();
	Enemy* Ep;
	for (int i = 0; i < ActiveCount; i++)
	{
		Q_Active.dequeue(Ep);
		if (Ep->GetType() == 0)
		{
			AddtoFightersList(Ep);
		}
		else if (Ep->GetType() == 1)
		{
			AddtoHealersList(Ep);
		}
		else if (Ep->GetType() == 2)
		{
			AddtoFreezersList(Ep);
		}
		Q_Active.enqueue(Ep);
	}
	for (int i = 0; i < FrostedCount; i++)
	{
		Q_Frosted_List.dequeue(Ep);
		if (Ep->GetType() == 0)
		{
			AddtoFightersList(Ep);
		}
		else if (Ep->GetType() == 1)
		{
			AddtoHealersList(Ep);
		}
		else if (Ep->GetType() == 2)
		{
			AddtoFreezersList(Ep);
		}
		Q_Frosted_List.enqueue(Ep,Ep->GetFreezeDuration());
	}
}

void Battle::PrepareFrozenPQ()
{
}

void Battle::EmptyFighterList()
{
	Enemy* Ep;
	while (!Q_Fighters.isEmpty())
	{
		Q_Fighters.dequeue(Ep);
	}
	FighterCount = 0;
}

void Battle::EmptyHealerList()
{
	Enemy* Ep;
	while (!S_Healers.isEmpty())
	{
		S_Healers.pop();
	}
	HealerCount = 0;
}
void Battle::EmptyFreezerList()
{
	Enemy* Ep;
	while (!Q_Freezers.isEmpty())
	{
		Q_Freezers.dequeue(Ep);
	}
	FreezerCount = 0;
}
void Battle::EmptyFrozenList()
{
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
	pGUI->UpdateInterface(CurrentTimeStep, GetCastle()->GetHealth(), GetCastle()->GetisCastleFrosted(),
		FighterCount, FreezerCount, HealerCount, ActiveCount,
		FrozenFighterCount, FrozenFreezerCount, FrozenHealerCount, FrostedCount,
		KilledFighterCount, KilledFreezerCount, KilledHealerCount, KilledCount);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();
	Enemy* Ep;
	//int battlestep = 0;
	while (((Q_Inactive.peekFront(Ep)) || ActiveCount>0 || FrostedCount > 0) && BCastle.GetHealth() > 0)	//as long as some enemies are alive (should be updated in next phases)
	{
	CurrentTimeStep++;
	ActivateEnemies();
	UpdateEnemies();
	if (BCastle.GetFreezeind() == 2 || BCastle.GetFreezeind() == 0)
	{
		BCastle.SetFreezeind(0);
		BCastle.AttackActive(Q_Fighters, S_Healers, Q_Freezers, FighterCount, HealerCount, FreezerCount, CurrentTimeStep);
	}
	else
	{
		BCastle.SetFreezeind(2);
	}
	PrepareActiveList();
	pGUI->ResetDrawingList();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep, GetCastle()->GetHealth(), GetCastle()->GetisCastleFrosted(),
		FighterCount, FreezerCount, HealerCount, ActiveCount,
		FrozenFighterCount, FrozenFreezerCount, FrozenHealerCount, FrostedCount,
		KilledFighterCount, KilledFreezerCount, KilledHealerCount, KilledCount);
	//pGUI->waitForClick(); //THis is step by step, so we wait for one second
	Sleep(1000);
	}

	if (BCastle.GetHealth() == 0)
	{
		IsGameLoss = true;
	}
	else if ((!Q_Inactive.peekFront(Ep)) || ActiveCount == 0 || FrostedCount == 0)
	{
		IsGameWin = true;
	}

}

void Battle::InterActive_Mode()
{
	CurrentTimeStep = 0; //reset time step 
	getinput();			//Get Input from file
	AddAllListsToDrawingList();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pGUI->UpdateInterface(CurrentTimeStep, GetCastle()->GetHealth(),GetCastle()->GetisCastleFrosted(),
	    FighterCount,FreezerCount, HealerCount,ActiveCount,
		FrozenFighterCount,FrozenFreezerCount,FrozenHealerCount,FrostedCount,
		KilledFighterCount,KilledFreezerCount,KilledHealerCount,KilledCount);	//upadte interface to show the initial case where all enemies are still inactive
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	pGUI->waitForClick();
	Enemy* Ep;
	while (((Q_Inactive.peekFront(Ep)) || ActiveCount > 0 || FrostedCount > 0) && BCastle.GetHealth() > 0)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		UpdateEnemies();
		if (BCastle.GetFreezeind() == 2 || BCastle.GetFreezeind() == 0)
		{
			BCastle.SetFreezeind(0);
			BCastle.AttackActive(Q_Fighters, S_Healers, Q_Freezers, FighterCount, HealerCount, FreezerCount, CurrentTimeStep);
		}
		else
		{
			BCastle.SetFreezeind(2);
		}
		PrepareActiveList();
		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep, GetCastle()->GetHealth(), GetCastle()->GetisCastleFrosted(),
			FighterCount, FreezerCount, HealerCount, ActiveCount,
			FrozenFighterCount, FrozenFreezerCount, FrozenHealerCount, FrostedCount,
			KilledFighterCount, KilledFreezerCount, KilledHealerCount, KilledCount);
		//pGUI->waitForClick(); //THis is step by step, so we wait for one second
		pGUI->waitForClick(); //THis is Interactive, so we wait for click
	}
}

void Battle::PrepareActiveList()
{
	int WhileTemp = ActiveCount;
	Enemy* Ep;
	for (int i = 0; i < WhileTemp; i++)
	{
		Q_Active.dequeue(Ep);
		if (Ep->GetHealth() <= 0)
		{
			if (Ep->GetType() == 0)
			{
				FighterCount--;
				KilledFighterCount++;
			}
			else if (Ep->GetType() == 1)
			{
				HealerCount--;
				KilledHealerCount++;
			}
			else
			{
				FreezerCount--;
				KilledFreezerCount++;
			}
			ActiveCount--;
			Ep->SetStatus(KILD);
			Ep->SetKTS(this->CurrentTimeStep);
			AddtoKilledList(Ep);
			continue;
		}
		if (Ep->GetFreezeDuration() >0)
		{
			Ep->SetStatus(FRST);
			if (Ep->GetType() == 0)
			{
				FighterCount--;
				FrozenFighterCount++;
			}
			else if (Ep->GetType() == 1)
			{
				HealerCount--;
				FrozenHealerCount++;
			}
			else
			{
				FreezerCount--;
				FrozenFreezerCount++;
			}
			ActiveCount--;
			AddtoFrostedList(Ep);
			continue;
		}
		Q_Active.enqueue(Ep);
	}
	int fortemp = FrostedCount;
	for (int i = 0; i < fortemp; i++)
	{
		Q_Frosted_List.dequeue(Ep);
		if (Ep->GetHealth() <= 0)
		{
			if (Ep->GetType() == 0)
			{
				FrostedCount--;
				FrozenFighterCount--;
				KilledFighterCount++;
			}
			else if (Ep->GetType() == 1)
			{
				FrostedCount--;
				FrozenHealerCount--;
				KilledHealerCount++;
			}
			else
			{
				FrostedCount--;
				FrozenFreezerCount--;
				KilledFreezerCount++;
			}
			ActiveCount--;
			Ep->SetStatus(KILD);
			Ep->SetKTS(CurrentTimeStep);
			AddtoKilledList(Ep);
			continue;
		}
		Q_Frosted_List.enqueue(Ep,Ep->GetFreezeDuration());
	}
	PrepareListsP_Q_S();
	ProcessFrostedList();
}


//Kareem
//Get input function that takes in the parameters of the game mode from input file
void Battle::getinput()
{
	fstream file("input.txt");    // setting input file
	double ch;
	int n, cp;
	file >> ch;  // retreiving castle health from input file
	file >> n;   // retreiving castle attacks from input file
	file >> cp;  // retreiving castle power from input file
	BCastle.SetHealth(ch);
	BCastle.SetOriginalHealth(ch);    // setting castle health by value obtained from input file
	BCastle.SetAtkPerTurn(n);         // setting castle attacks by value obtained from input file
	BCastle.SetPower(cp);             // setting castle power by value obtained from input file
	int count;
	file >> count;    // retreiving total nu,ber of enemies
	EnemyCount = count;
	int id, Type, AT, RLD;  // declaring variables that hold enemies info
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
		file >> SPD;      // retreiving enemy info from input file and setting the info to its respective variable

		if (Type == 0)
		{
			eptr = new Fighter(id, Type, AT, H, POW, RLD, SPD);     // creating a new fighter based on info retreived from input file
		}
		else if (Type == 1)
		{
			eptr = new Healer(id, Type, AT, H, POW, RLD, SPD);      // creating a new healer based on info retreived from input file
		}
		else
		{
			Type = 2;
			eptr = new Freezer(id, Type, AT, H, POW, RLD, SPD);     // creating a new fighter based on info retreived from input file
		}
		eptr->SetStatus(INAC);   // setting newly created enemy to be inactive
		Q_Inactive.enqueue(eptr);  // adding newly created enemy to inactive list
	}
}

void Battle::CreateOutput()
{
	ofstream output("Output.txt");   // setting output file
	string game = "Game is ";
	if (IsGameWin == true)
	{
		game = game + "Win";      //creating game is win string if game was won
	}
	else
	{
		if (IsGameLoss == true)       
		{
			game = game + "Loss";    //creating game is loss string if game was loss
		}
		else
		{
			game = game + "Drawn";   // if game was neither win nor loss then it is drawn 
		}
	}

	output << game << endl;         // adding game is string to output file
	output << "KTS    ID     FD     KD     LT" << endl;       // adding required layout as instructed in project document 

	int KilledEnemies = KilledFighterCount + KilledFreezerCount + KilledHealerCount;  // getting number of killed enemies

	Queue<Enemy*> temp;       // declaring variables that will hold enemy info to then be added to output file
	Enemy* eptr = nullptr;
	int sumfirstshotdelay = 0;
	int sumkilldelay = 0;
	int id =0;
	int KTS = 0;
	int FD = 0;
	int KD = 0;
	int LT = 0;
	int FSTS = 0;

	while (!(Q_Killed_List.isEmpty()))     // as long as killed queue has enemies each enemy is dequeued and info required about enemies is set to their respective variables previously created 
	{
		Q_Killed_List.dequeue(eptr);
		KTS = eptr->GetKTS();
		FSTS = eptr->GetFSTS();
		FD = FSTS - (eptr->GetArrvTime());
		KD = KTS - FSTS;
		LT = FD + KD;
		id = eptr->GetID();
		sumfirstshotdelay = sumfirstshotdelay + FD;   // at end of loop will contain sum of first shot delay of enemies
		sumkilldelay = sumkilldelay + KD;    // at end of loop will contain sum of kill delay of enemies
		temp.enqueue(eptr);      // enqueuing enemies in a temp queue 
		output << SetformatOutput(KTS) << SetformatOutput(id) << SetformatOutput(FD) << SetformatOutput(KD) << SetformatOutput(LT) << endl; // adding each enemy info to output file and using setformatoutput to ensure table structure for enemy info in output file
	}

	while (!(temp.isEmpty()))
	{
		temp.dequeue(eptr);
		Q_Killed_List.enqueue(eptr);  // returning enemy pointers to killed queue
	}

	double TotalCastleDamage = BCastle.GetOriginalHealth()-BCastle.GetHealth();    // calculating total castle damage by obtaining its original hp and current hp 
	output << "Castle Total Damage = " << TotalCastleDamage << endl;   // adding castle damage to output file 

	if (IsGameWin == true)     // adding required info incase game was won or loss/drawn 
	{
		output << "Total Killed Enemies = " << KilledEnemies << endl;
		output << "Average First-Shot delay = " << (sumfirstshotdelay / KilledEnemies) << endl; // getting average by dividing sum and number of enemies that contributed to sum
		output << "Average Kill Delay = " << (sumkilldelay / KilledEnemies) << endl;
		return;
	}
	else
	{
		output << "Total Killed Enemies = " << KilledEnemies << endl;
		output << "Total Alive Enemies = " << (EnemyCount - KilledEnemies) << endl;  // calculating active by subtracting killed from total enemy count
		output << "Average First-Shot delay for killed enemies = " << (sumfirstshotdelay / KilledEnemies) << endl;
		output << "Average Kill Delay for killed enemies = " << (sumkilldelay / KilledEnemies) << endl;
		return;
	}
}

string Battle::SetformatOutput(int x)  // returns a string that maintains table format for enemy info in output file 
{
	string r;
	r = to_string(x);
	if (x < 10)
	{
		return r + "      ";
	}
	if (x < 100)
	{
		return r + "     ";
	}
	if (x < 1000)
	{
		return r + "    ";
	}
	if (x < 10000)
	{
		return r + "   ";
	}
	if (x < 100000)
	{
		return r + "  ";
	}
	if (x < 1000000)
	{
		return r + " ";
	}
	if (x < 10000000)
	{
		return r + "";
	}
}