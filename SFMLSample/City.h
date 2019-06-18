#pragma once
#ifndef CITY_H
#define CITY_H

#include "pch.h"

class City
{
	std::vector <std::vector <BuildingInstance*>> buildings; /// Wektor budynków


public:

	City();
	City(std::vector <std::vector <Building*>> setOfBuildings);
	City(Building* building, sf::Vector2i index);
	City(Building* building, std::pair<short, short> index);
	City(Building* building, short x, short y);

	void setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings);
	
	void setSpecificBuilding(Building* building, sf::Vector2i index);
	void setSpecificBuilding(Building* building, std::pair<short, short> index);
	void setSpecificBuilding(Building* building, short x, short y);

	void deleteBuilding(sf::Vector2i index);
	void deleteBuilding(std::pair <short, short> index);
	void deleteBuilding(short x, short y);

	BuildingInstance* getBuilding(sf::Vector2i index) { return buildings[index.x][index.y]; }
	BuildingInstance* getBuilding(std::pair<short, short> index) { return buildings[index.first][index.second]; }
	BuildingInstance* getBuilding(short x, short y) { return buildings[x][y]; }
};

#endif /*CITY_H*/

