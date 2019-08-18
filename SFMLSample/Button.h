#pragma once
#include "pch.h" 
class Button
{
	Function* activationFunction;

public:
	Button();
	~Button();
	void setActivationFunction(Function* newActivationFunction) { activationFunction = newActivationFunction; }
	Function* getActivationFunction() { return activationFunction; }
};

