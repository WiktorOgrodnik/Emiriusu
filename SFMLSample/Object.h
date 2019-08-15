#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "pch.h"

class Object
{
public:
	Object() {} /// konstruktor
	virtual ~Object() {} /// destruktor
	virtual void draw(sf::RenderWindow& window) = 0; /// wirtualna funkcja rysowania
	virtual void draw(sf::RenderWindow& window, sf::View& view, float zoom) = 0; /// wirtualna funkcja rysowania (tylko mapa u¿ywa tej funkcji!)
	virtual void draw(sf::RenderTexture& texture) = 0;
};

///Engine Depracted Functions

class DebugObject : public Object 
{
	sf::Texture* texture;
	sf::RectangleShape body;

public:
	void draw(sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override { draw(window); }
	void draw(sf::RenderTexture& texture) override { texture.draw(body); }
	
	DebugObject(sf::Texture* newTexture, int x, int y);
};

#endif /* OBJECT_H */

