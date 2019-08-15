#pragma once
#ifndef TYPES_H
#define TYPES_H

#include "pch.h"

class Type
{
};

class Biome : public Type 
{
	int id; /// id kafelka
	std::string name; 
	sf::Color biomeColor;
	float moveCost;
	float opacity;
	short food;
	short stone;
	short wood;
	bool canBuildACity;
	bool canWalkThru;
	std::string specialStuff;

public:

	Biome(std::string fileName);
	std::string getName() { return name; }
	int getId() { return id; }
	float getMoveCost() { return moveCost; }
	short getFood() { return food; }
	short getStone() { return stone; }
	short getWood() { return wood; }
	bool getCanBuildACity() { return canBuildACity; }
	bool getCanWalkThru() { return canWalkThru; }
	std::string getSpecialStuff() { return specialStuff; }
	void setColor(char r, char g, char b, char transparency)
	{
		biomeColor.r = r; biomeColor.g = g; biomeColor.b = b;
	}
	sf::Color* getBiomeColor() { return &biomeColor; }
};

class BiomeAddOn : public Type
{
public:
};

class Building
{
	std::string name;
	std::string texture;
	bool canEdit;

public:

	Building(std::string fileName);
	void setCanEdit(bool canEdit_);

	std::string getName() { return name; }
	std::string getTextureId() { return texture; }
	bool getCanEdit() { return canEdit; }

};

class BuildingInstance : public Object
{
	Building* type;
	sf::Texture* texture;
	sf::RectangleShape body;
	sf::Vector2f position; /// pierwsza wartoœæ to indeks x, a druga to index y

public:

	void draw(sf::RenderWindow& window) override; /// witualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u¿ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	BuildingInstance(Building* newType, sf::Vector2f rootPos, std::pair<unsigned, unsigned> additionalPos);
	BuildingInstance(Building* newType, sf::Vector2f rootPos, std::pair<unsigned, unsigned> additionalPos, Player* player);

	void setType(Building* newType);
	Building* getType() { return type; }
};

class Mineral : public Type
{
public:
};

#endif /* TYPES_H */

