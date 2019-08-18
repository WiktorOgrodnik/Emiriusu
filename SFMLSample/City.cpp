#include "pch.h"
#include "City.h"

City::City(sf::Vector2f newPosition, Player* player)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(position.x) + " " + std::to_string(position.y));

	Engine::getInstance().getGlobalMap()->getTile(int(position.x), int(position.y))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(owner->getFraction(), std::to_string(owner->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	makeClearVectorOfBuildings();

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, std::vector <std::vector <Building*>> setOfBuildings)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(position.x) + " " + std::to_string(position.y));

	Engine::getInstance().getGlobalMap()->getTile(int(position.x), int(position.y))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(owner->getFraction(), std::to_string(owner->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	makeClearVectorOfBuildings();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			setSpecificBuilding(setOfBuildings[i][j], std::make_pair(i, j));
		}
	}

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, Building* building, sf::Vector2i index)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(position.x) + " " + std::to_string(position.y));

	Engine::getInstance().getGlobalMap()->getTile(int(position.x), int(position.y))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(owner->getFraction(), std::to_string(owner->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	makeClearVectorOfBuildings();

	setSpecificBuilding(building, index);

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, Building* building, std::pair<short, short> index)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(position.x) + " " + std::to_string(position.y));

	Engine::getInstance().getGlobalMap()->getTile(int(position.x), int(position.y))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), std::to_string(player->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	makeClearVectorOfBuildings();

	setSpecificBuilding(building, index);

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, Building* building, short x, short y)
{

	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(position.x) + " " + std::to_string(position.y));

	Engine::getInstance().getGlobalMap()->getTile(int(position.x), int(position.y))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(owner->getFraction(), std::to_string(owner->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	setSpecificBuilding(building, x, y);

	Engine::getInstance().addToRenderObjects(this, 1);

}

void City::setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			setSpecificBuilding(setOfBuildings[i][j], std::make_pair(i, j));
		}
	}
}

void City::setSpecificBuilding(Building* building, sf::Vector2i index)
{
	if (existBuilding(index)) deleteBuilding(index);
	buildings[index.x][index.y] = new BuildingInstance(building, position, std::make_pair(index.x * miniTileResolution, index.y * miniTileResolution), owner, std::make_pair(index.x, index.y));
	Engine::getInstance().getData().reportBuildingInstance(getBuilding(index), this);
	getBuilding(index)->addToDistrict();
}

void City::setSpecificBuilding(Building* building, std::pair<short, short> index)
{
	if (existBuilding(index)) deleteBuilding(index);
	buildings[index.first][index.second] = new BuildingInstance(building, position, std::make_pair(index.first * miniTileResolution, index.second * miniTileResolution), owner, index);
	Engine::getInstance().getData().reportBuildingInstance(buildings[index.first][index.second], this);
	getBuilding(index)->addToDistrict();
}

void City::setSpecificBuilding(Building* building, short x, short y)
{
	if (existBuilding(x, y)) deleteBuilding(x, y);
	buildings[x][y] = new BuildingInstance(building, position, std::make_pair(x * miniTileResolution, y * miniTileResolution), owner, std::make_pair(x, y));
	Engine::getInstance().getData().reportBuildingInstance(buildings[x][y], this);
	getBuilding(x, y)->addToDistrict();
}

void City::deleteBuilding(sf::Vector2i index)
{
	if (existBuilding(index))
	{
		delete buildings[index.x][index.y];
		buildings[index.x][index.y] = nullptr;
	}
	else Log::newLog("Tu nie ma budynku");
}

void City::deleteBuilding(std::pair <short, short> index)
{
	if (existBuilding(index))
	{
		delete buildings[index.first][index.second];
		buildings[index.first][index.second] = nullptr;
	}
	else Log::newLog("Tu nie ma budynku");
}

void City::deleteBuilding(short x, short y)
{
	if (existBuilding(x, y))
	{
		delete buildings[x][y];
		buildings[x][y] = nullptr;
	}
	else Log::newLog("Tu nie ma budynku");
}

void City::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void City::draw(sf::RenderWindow& window, sf::View& view, float zoom)
{
	window.draw(body);
}

void City::draw(sf::RenderTexture& texture)
{
	texture.draw(body);
}

Function* City::onSelect()
{
	return nullptr;
}

Function* City::onClick()
{
	return nullptr;
}

Function* City::onDeselect()
{
	return nullptr;
}

void City::setOwner(Player* newPlayer)
{
	owner = newPlayer;
}

Player* City::getOwner()
{
	return owner;
}

void City::makeClearVectorOfBuildings()
{
	buildings.resize(3);

	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
}

std::vector <BuildingInstance*> City::getFriends(std::pair <short, short> pos)
{
	std::vector <BuildingInstance*> friends;

	try
	{
		//Lewo 
		if (pos.first != 0)
		{
			if (existBuilding(std::make_pair(pos.first - 1, pos.second)))
			{
				if (getBuilding(pos)->getType()->getDistrictType() == getBuilding(std::make_pair(pos.first - 1, pos.second))->getType()->getDistrictType())
				{
					if (!getBuilding(std::make_pair(pos.first - 1, pos.second))->getLock()) friends.push_back(getBuilding(std::make_pair(pos.first - 1, pos.second)));
				}
			}
		}
		else
		{
			if (position.x != 0)
			{
				if (Engine::getInstance().getGlobalMap()->getTile(position.x - 1, position.y)->checkIfCity())
				{
					City* t = Engine::getInstance().getGlobalMap()->getTile(position.x - 1, position.y)->getCity();
					if (t->getOwner() == owner)
					{
						if (t->existBuilding(2, pos.second))
						{
							if (getBuilding(pos)->getType()->getDistrictType() == t->getBuilding(std::make_pair(2, pos.second))->getType()->getDistrictType())
							{
								if (!t->getBuilding(std::make_pair(2, pos.second))->getLock()) friends.push_back(t->getBuilding(2, pos.second));
							}
						}
					}
				}
			}
		}


		//Góra
		if (pos.second != 0)
		{
			if (existBuilding(std::make_pair(pos.first, pos.second - 1)))
			{
				if (getBuilding(pos.first, pos.second - 1)->getType()->getDistrictType() == getBuilding(pos)->getType()->getDistrictType())
				{
					if (!getBuilding(std::make_pair(pos.first, pos.second - 1))->getLock()) friends.push_back(getBuilding(std::make_pair(pos.first, pos.second - 1)));
				}
			}
		}
		else
		{
			if (position.y != 0)
			{
				if (Engine::getInstance().getGlobalMap()->getTile(position.x, position.y - 1)->checkIfCity())
				{
					City* t = Engine::getInstance().getGlobalMap()->getTile(position.x, position.y - 1)->getCity();
					if (t->getOwner() == owner)
					{
						if (t->existBuilding(pos.first, 2))
						{
							if (getBuilding(pos)->getType()->getDistrictType() == t->getBuilding(std::make_pair(pos.first, 2))->getType()->getDistrictType())
							{
								if (!t->getBuilding(std::make_pair(pos.first, 2))->getLock()) friends.push_back(t->getBuilding(pos.first, 2));
							}
						}
					}
				}
			}
		}


		//Dó³
		if (pos.second != 2)
		{
			if (existBuilding(std::make_pair(pos.first, pos.second + 1)))
			{
				if (getBuilding(pos)->getType()->getDistrictType() == getBuilding(std::make_pair(pos.first, pos.second + 1))->getType()->getDistrictType())
				{
					if (!getBuilding(std::make_pair(pos.first, pos.second + 1))->getLock()) friends.push_back(getBuilding(std::make_pair(pos.first, pos.second + 1)));
				}
			}
		}
		else
		{
			if (position.y != Engine::getInstance().getData().World().getMapSize() - 1)
			{
				if (Engine::getInstance().getGlobalMap()->getTile(position.x, position.y + 1)->checkIfCity())
				{
					City* t = Engine::getInstance().getGlobalMap()->getTile(position.x, position.y + 1)->getCity();
					if (t->getOwner() == owner)
					{
						if (t->existBuilding(pos.first, 0))
						{
							if (getBuilding(pos)->getType()->getDistrictType() == t->getBuilding(std::make_pair(pos.first, 0))->getType()->getDistrictType())
							{
								if (!t->getBuilding(std::make_pair(pos.first, 0))->getLock()) friends.push_back(t->getBuilding(pos.first, 0));
							}
						}
					}
				}
			}
		}


		//Prawo
		if (pos.first != 2)
		{
			if (existBuilding(std::make_pair(pos.first + 1, pos.second)))
			{
				if (getBuilding(pos)->getType()->getDistrictType() == getBuilding(std::make_pair(pos.first + 1, pos.second))->getType()->getDistrictType())
				{
					if (getBuilding(std::make_pair(pos.first + 1, pos.second))->getLock() == false) friends.push_back(getBuilding(std::make_pair(pos.first + 1, pos.second)));
				}
			}
		}
		else
		{
			if (position.x != Engine::getInstance().getData().World().getMapSize() - 1)
			{
				if (Engine::getInstance().getGlobalMap()->getTile(position.x + 1, position.y)->checkIfCity())
				{
					City* t = Engine::getInstance().getGlobalMap()->getTile(position.x + 1, position.y)->getCity();
					if (t->getOwner() == owner)
					{
						if (t->existBuilding(0, pos.second))
						{
							if (getBuilding(pos)->getType()->getDistrictType() == t->getBuilding(std::make_pair(0, pos.second))->getType()->getDistrictType())
							{
								if (t->getBuilding(std::make_pair(0, pos.second))->getLock() == false) friends.push_back(t->getBuilding(0, pos.second));
							}
						}
					}
				}
			}
		}
	}
	catch (std::string exception) { Log::newLog("Nastapi³ wyj¹tek" + exception); }

	return friends;
}

bool City::existBuilding(sf::Vector2i index)
{
	if (getBuilding(index) == nullptr) return false;
	return true;
}

bool City::existBuilding(std::pair <short, short> index)
{
	if (getBuilding(index) == nullptr) return false;
	return true;
}

bool City::existBuilding(short x, short y)
{
	if (getBuilding(x, y) == nullptr) return false;
	return true;
}

BuildingInstance* City::getBuilding(sf::Vector2i index)
{
	return buildings[index.x][index.y];
}
BuildingInstance* City::getBuilding(std::pair<short, short> index)
{ 
	return buildings[index.first][index.second]; 
}
BuildingInstance* City::getBuilding(short x, short y)
{ 
	return buildings[x][y]; 
}