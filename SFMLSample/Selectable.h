#pragma once

#include "pch.h"

class Selectable
{
public:
	Selectable();
	~Selectable();
	Function* onClickFunction;
	Function* onReleaseFunction;
	Function* onDeselectFunction;
};

