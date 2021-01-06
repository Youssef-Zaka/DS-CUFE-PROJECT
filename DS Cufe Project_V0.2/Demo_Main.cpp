#include "Battle.h"
#include "GUI\GUI.h"
//#include "Generic_DS/PQueue.h"
//#include "Enemies/Enemy.h"

int main()
{
	
	Battle* pGameBattle = new Battle;
	pGameBattle->RunSimulation();
	
	delete pGameBattle;
	
	return 0;
}

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