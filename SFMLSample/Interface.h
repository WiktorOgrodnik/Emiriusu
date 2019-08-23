#pragma once
#include "pch.h"
class Interface
{
public:
	Interface() {} /// konstruktor
	virtual ~Interface() {} /// destruktor
	virtual void render(sf::RenderTarget* target) = 0; /// wirtualna funkcja rysowania
};


