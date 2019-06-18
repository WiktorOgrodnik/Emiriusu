#include "pch.h"
#include "City.h"

City::City()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
}

City::City(std::vector <std::vector <Building*>> setOfBuildings)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(setOfBuildings[i][j]);
		}
	}
}

City::City(Building* building, sf::Vector2i index)
{
	buildings[index.x][index.y] = new BuildingInstance(building);
}

City::City(Building* building, std::pair<short, short> index)
{
	buildings[index.first][index.second] = new BuildingInstance(building);
}

City::City(Building* building, short x, short y)
{
	buildings[x][y] = new BuildingInstance(building);
}

void City::setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(setOfBuildings[i][j]);
		}
	}
}

void City::setSpecificBuilding(Building* building, sf::Vector2i index)
{
	buildings[index.x][index.y] = new BuildingInstance(building);
}

void City::setSpecificBuilding(Building* building, std::pair<short, short> index)
{
	buildings[index.first][index.second] = new BuildingInstance(building);
}

void City::setSpecificBuilding(Building* building, short x, short y)
{
	buildings[x][y] = new BuildingInstance(building);
}

void City::deleteBuilding(sf::Vector2i index)
{
	if (buildings[index.x][index.y] != nullptr)
	{
		delete buildings[index.x][index.y];
		buildings[index.x][index.y] = nullptr;
	}
	else std::cerr << "Tu nie ma budynku\n";
}

void City::deleteBuilding(std::pair <short, short> index)
{
	if (buildings[index.first][index.second] != nullptr)
	{
		delete buildings[index.first][index.second];
		buildings[index.first][index.second] = nullptr;
	}
	else std::cerr << "Tu nie ma budynku\n";
}

void City::deleteBuilding(short x, short y)
{
	if (buildings[x][y] != nullptr)
	{
		delete buildings[x][y];
		buildings[x][y] = nullptr;
	}
	else std::cerr << "Tu nie ma budynku\n";
}
