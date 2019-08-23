#pragma once
#include "pch.h"

class Interface
{

protected:

	Function* IdleFunction;
	Function* HoverFunction;
	Function* ActiveFunction;

public:

	virtual Function* Inactive() = 0;
	virtual Function* Hover() = 0;
	virtual Function* Active() = 0;

	Interface(); /// konstruktor
	virtual ~Interface() {} /// destruktor
	virtual void render(sf::RenderTarget* target) = 0; /// wirtualna funkcja rysowania
	virtual void render(sf::RenderWindow* window) = 0;
	virtual bool checkMousePoints(sf::Vector2f pos) = 0;
};


