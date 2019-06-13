#pragma once

#include "pch.h"

class Unit
{
	std::vector<Function*> unitFunctions;
public:
	Unit();
	~Unit();

	float numberOfMoves;
	unsigned unitCount;
	///inne statystyki 
};

