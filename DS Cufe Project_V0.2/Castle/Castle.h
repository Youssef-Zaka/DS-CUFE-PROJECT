#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	
	//
	// TODO: Add More Data Members As Needed
	//
	//Members added by ZAKA//

	int NumAtkPerTurn; //ZAKA:: Number of enemies the castle may attack per turn, This value is retrieved from input file.
	int CastlePower; // Castle Power retrived from input file.

	bool isCastleFrosted;

public:

	void SetHealth(double h);
	double GetHealth() const;

	void SetPower(int h);
	int GetPower() const;

	void SetAtkPerTurn(int h);
	int GetAtkPerTurn() const;


	void SetisCastleFrosted(bool b);
	bool GetisCastleFrosted() const;
	//
	// TODO: Add More Member Functions As Needed
	//
};

