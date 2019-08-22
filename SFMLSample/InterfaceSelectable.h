#pragma once
#include "pch.h"
class InterfaceSelectable
{
protected:
	Function* IdleFunction;
	Function* HoverFunction;
	Function* ActiveFunction;
public:
	InterfaceSelectable();
	~InterfaceSelectable();
	virtual Function* Idle() = 0;
	virtual Function* Hover() = 0;
	virtual Function* Active() = 0;
};

