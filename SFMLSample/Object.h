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

class miniTile : public Object ///Przeznaczone do usuniêcia
{
	sf::Texture *texture;
	sf::RectangleShape body;
	short type;

public:
	void draw(sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override { draw(window); }
	void draw(sf::RenderTexture& texture) override { texture.draw(body); }
	
	miniTile(sf::Texture* newTexture, int x, int y);
};

#endif /* OBJECT_H */

