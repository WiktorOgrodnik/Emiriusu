#pragma once
#ifndef TYPES_H
#define TYPES_H

#include "pch.h"

class Biome
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

class BiomeAddOn
{
public:
};

class Building
{
	std::string name;
	bool canEdit;

public:

	Building(std::string name_);
	void setCanEdit(bool canEdit_);

	std::string getName() { return name; }
	bool getCanEdit() { return canEdit; }

};

class BuildingInstance
{
	Building* type;
public:

	BuildingInstance(Building* newType);

	void setType(Building* newType);
	Building* getType() { return type; }
};

class Mineral
{
public:
};

#endif /* TYPES_H */

