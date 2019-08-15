#include "pch.h"

//Engine Depracted Functions:

void DebugObject::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

DebugObject::DebugObject(sf::Texture* newTexture, int x, int y)
{
	body.setSize(sf::Vector2f(tileResolution * x, tileResolution * y));
	texture = newTexture;
	body.setTexture(texture);
}
