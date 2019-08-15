#include "pch.h"
#include "City.h"

City::City(sf::Vector2f newPosition, Player* player)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), std::to_string(player->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	buildings.resize(3);

	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, std::vector <std::vector <Building*>> setOfBuildings)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), std::to_string(player->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	buildings.resize(3);

	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(setOfBuildings[i][j], position, std::make_pair(i * miniTileResolution, j * miniTileResolution));
		}
	}

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, Building* building, sf::Vector2i index)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), std::to_string(player->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	buildings[index.x][index.y] = new BuildingInstance(building, position, std::make_pair(index.x * miniTileResolution, index.y * miniTileResolution));

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, Building* building, std::pair<short, short> index)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), std::to_string(player->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	buildings[index.first][index.second] = new BuildingInstance(building, position, std::make_pair(index.first * miniTileResolution, index.second * miniTileResolution));

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, Player* player, Building* building, short x, short y)
{
	owner = player;

	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), std::to_string(player->getPlayerAdvanceLevel()));
	body.setTexture(texture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	buildings[x][y] = new BuildingInstance(building, position, std::make_pair(x * miniTileResolution, y * miniTileResolution));

	Engine::getInstance().addToRenderObjects(this, 1);
}

void City::setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(setOfBuildings[i][j], position, std::make_pair(i * miniTileResolution, j * miniTileResolution));
		}
	}
}

void City::setSpecificBuilding(Player* player, Building* building, sf::Vector2i index)
{
	buildings[index.x][index.y] = new BuildingInstance(building, position, std::make_pair(index.x * miniTileResolution, index.y * miniTileResolution), player);
}

void City::setSpecificBuilding(Player* player, Building* building, std::pair<short, short> index)
{
	buildings[index.first][index.second] = new BuildingInstance(building, position, std::make_pair(index.first * miniTileResolution, index.second * miniTileResolution), player);
}

void City::setSpecificBuilding(Player* player, Building* building, short x, short y)
{
	buildings[x][y] = new BuildingInstance(building, position, std::make_pair(x * miniTileResolution, y * miniTileResolution), player);
}

void City::deleteBuilding(sf::Vector2i index)
{
	if (buildings[index.x][index.y] != nullptr)
	{
		delete buildings[index.x][index.y];
		buildings[index.x][index.y] = nullptr;
	}
	else Log::newLog("Tu nie ma budynku");
}

void City::deleteBuilding(std::pair <short, short> index)
{
	if (buildings[index.first][index.second] != nullptr)
	{
		delete buildings[index.first][index.second];
		buildings[index.first][index.second] = nullptr;
	}
	else Log::newLog("Tu nie ma budynku");
}

void City::deleteBuilding(short x, short y)
{
	if (buildings[x][y] != nullptr)
	{
		delete buildings[x][y];
		buildings[x][y] = nullptr;
	}
	else Log::newLog("Tu nie ma budynku");
}

void City::draw(sf::RenderWindow& window)
{
	window.draw(body);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j]->draw(window);
		}
	}
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
