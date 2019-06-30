#pragma once
#include "pch.h"

class Function
{
	Types retunedType;
public:
	Function();
	virtual ~Function();
	virtual void* Activate(std::vector<void*> data) = 0;
	Types getReturnedType() { return retunedType; }
	void setReturnedType(Types newReturnedType) { retunedType = newReturnedType; }
};

class Dijkstra : Function
{
	void* Activate(std::vector<void*> data) override;
};

