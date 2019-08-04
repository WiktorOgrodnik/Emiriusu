#include "pch.h"
#include "City.h"

City::City(sf::Vector2f newPosition, sf::Texture* newTexture)
{
	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;
	
	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = newTexture;
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	cityType = 0;
	cityExtra = 0;

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

City::City(sf::Vector2f newPosition, sf::Texture* newTexture, std::vector <std::vector <Building*>> setOfBuildings)
{
	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = newTexture;
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	cityType = 0;
	cityExtra = 0;

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

City::City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, sf::Vector2i index)
{
	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = newTexture;
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	cityType = 0;
	cityExtra = 0;

	buildings[index.x][index.y] = new BuildingInstance(building, position, std::make_pair(index.x * miniTileResolution, index.y * miniTileResolution));

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, std::pair<short, short> index)
{
	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = newTexture;
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	cityType = 0;
	cityExtra = 0;

	buildings[index.first][index.second] = new BuildingInstance(building, position, std::make_pair(index.first * miniTileResolution, index.second * miniTileResolution));

	Engine::getInstance().addToRenderObjects(this, 1);
}

City::City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, short x, short y)
{
	position.x = newPosition.x / tileResolution;
	position.y = newPosition.y / tileResolution;

	Log::newLog("Tworzê miasto na pozycji: " + std::to_string(newPosition.x / tileResolution) + " " + std::to_string(newPosition.y / tileResolution));

	Engine::getInstance().getGlobalMap()->getTile(int(newPosition.x / tileResolution), int(newPosition.y / tileResolution))->addSelectable(this);

	texture = newTexture;
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	cityType = 0;
	cityExtra = 0;

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

void City::setSpecificBuilding(Building* building, sf::Vector2i index)
{
	buildings[index.x][index.y] = new BuildingInstance(building, position, std::make_pair(index.x * miniTileResolution, index.y * miniTileResolution));
}

void City::setSpecificBuilding(Building* building, std::pair<short, short> index)
{
	buildings[index.first][index.second] = new BuildingInstance(building, position, std::make_pair(index.first * miniTileResolution, index.second * miniTileResolution));
}

void City::setSpecificBuilding(Building* building, short x, short y)
{
	buildings[x][y] = new BuildingInstance(building, position, std::make_pair(x * miniTileResolution, y * miniTileResolution));
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
