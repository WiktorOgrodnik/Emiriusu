#pragma once

#include "pch.h"

class Selectable
{
protected:
	Function onClickFunction;
	Function onReleaseFunction;
public:
	Selectable();
	~Selectable();
	virtual Function* onClick() = 0;
	virtual Function* onRelease() = 0;
};

