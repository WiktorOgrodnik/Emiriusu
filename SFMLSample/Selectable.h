#pragma once

#include "pch.h"

class Selectable
{
protected:
	Function* onClickFunction;
	Function* onSelectFunction;
	Function* onDeselectFunction;
public:
	Selectable();
	~Selectable();
	virtual Function* onSelect() = 0;
	virtual Function* onClick() = 0;
	virtual Function* onDeselect() = 0;
	
};

