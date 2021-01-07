#include "Battle.h"
#include "GUI\GUI.h"
//#include <iostream>	//USED IN RANDOM GENEREATION TEST
//#include <time.h>		//USED IN RANDOM GENEREATION TEST
//#include <chrono>		//USED IN RANDOM GENEREATION TEST
//#include "Generic_DS/PQueue.h" //USED IN P QUEUE TEST
//#include "Enemies/Enemy.h"	//USED IN P QUEUE TEST

int main()
{
	
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	
	delete pGameBattle;
	
	return 0;
}


//MAIN USED TO TEST PRIORITY QUEUE
//RESULTS: WORKING PROPERLY, WILL MOVE ON TO IMPLEMENTING CASTLE ACTIONS
//int main()
//{
//	Fighter* E1 = new Fighter(1,0,1,100,100,2,2);
//	Fighter* E2 = new Fighter(2,0,1,100,50,2,2);
//	Fighter* E3 = new Fighter(3,0,1,100,200,2,2);
//
//
//	PQueue<Enemy*> FighterQueue;
//	
//	FighterQueue.enqueue(E1,E1->GetPriority());
//	FighterQueue.enqueue(E2,E2->GetPriority());
//	FighterQueue.enqueue(E3,E3->GetPriority());
//
//	int x;
//	x = 1;
//}


//MAIN USED TO TEST RANDOM GENERATION PERCENTAGE
//RESULTS:
//FROM 1000 TRIES : 19.4%
//FROM 10k TRIES : 20.5%
//FROM 1M  TRIES : 20.1%
//FROM 1B  TRIES : 20.003%
//
//int main()
//{
//	int WhileHardNum = 1000000000;
//	double FreezeCount = 0;
//	double NonFreezeCount = 0;
//	srand(time(NULL));
//	auto start = std::chrono::high_resolution_clock::now();
//	while (WhileHardNum > 0)
//	{
//		bool TurnToFreeze;
//		int Random = rand() % 6;
//		TurnToFreeze = Random;
//		TurnToFreeze = !TurnToFreeze;
//		if (TurnToFreeze)
//		{
//			FreezeCount++;
//		}
//		else
//		{
//			NonFreezeCount++;
//		}
//		WhileHardNum--;
//	}
//	auto Stop = std::chrono::high_resolution_clock::now();
//	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(Stop - start);
//	std::cout << "Time Taken for excution was: " << (double)duration.count()/1000000 <<"Seconds" <<std::endl;
//	std::cout << "Percentage of Freeze from 1000000000 runs was: " << (double)(FreezeCount/NonFreezeCount)*100 << std::endl;
//	
//	
//}