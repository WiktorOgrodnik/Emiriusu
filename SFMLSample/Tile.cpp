#include "pch.h"
#include "Tile.h"

void Tile::setPosition(sf::Vector2f newPosition)
{
	position = newPosition;
}

void Tile::setPosition(float x, float y)
{
	position = sf::Vector2f(x, y);
}

void Tile::setRand()
{
	rng::uid = std::uniform_int_distribution<unsigned>(0, 19);
	rand_ = rng::uid(rng::mt);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
	type = newType;
	position = newPosition;
	riverType = 0;
	mineral = nullptr;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, char riverType_)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
	type = newType;
	position = newPosition;
	riverType = riverType_;
	mineral = nullptr;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral)
{
	rand_ = 0;
	setRand();
	
	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(newBuildings[i][j]);
		}
	}
	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(newBuildings[i][j]);
		}
	}
	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = nullptr;
		}
	}
	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(newBuildings[i][j]);
		}
	}
	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	buildings.resize(3);
	for (int i = 0; i < 3; i++)
	{
		buildings[i].resize(3);
		for (int j = 0; j < 3; j++)
		{
			buildings[i][j] = new BuildingInstance(newBuildings[i][j]);
		}
	}
	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = false;
}

void Tile::setCity(bool city_)
{
	city = city_;
}

void Tile::setRiver(char riverType_)
{
	buildings[1][1] = Engine::getInstance().getData().getRiverPlaceholderInstance();
	/// dlaczego nie tak ??? riverType |= riverType_; robi dok³adnie to samo
	/// ^ s³uszna uwaga

	if (riverType_ & (1 << 0))
	{
		buildings[0][1] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverType |= (1 << 0);
	}
	if (riverType_ & (1 << 1))
	{
		buildings[1][2] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverType |= (1 << 1);
	}
	if (riverType_ & (1 << 2))
	{
		buildings[2][1] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverType |= (1 << 2);
	}
	if (riverType_ & (1 << 3))
	{
		buildings[1][0] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverType |= (1 << 3);
	}
	if (riverType_ & (1 << 4))
	{
		buildings[0][0] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverExtra = 1;
	}
	else if (riverType_ & (1 << 5))
	{
		buildings[0][2] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverExtra = 2;
	}
	else if (riverType_ & (1 << 6)) 
	{
		buildings[2][0] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverExtra = 3;
	}
	else if (riverType_ & (1 << 7))
	{
		buildings[2][2] = Engine::getInstance().getData().getRiverPlaceholderInstance();
		riverExtra = 4;
	}
	else riverExtra = 0;
}

void Tile::setArmy(Selectable* newArmy)
{
	army = newArmy;
}

void Tile::setType(Biome* newType)
{
	type = newType;
}

void Tile::setMineral(Mineral* newMineral)
{
	mineral = newMineral;
}

void Tile::setSetOfBuildings(std::vector <std::vector<Building*>> newBuildings)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			buildings[i][j] = new BuildingInstance(newBuildings[i][j]);
		}
	}
}

void Tile::setAddOn(BiomeAddOn* newBiomeAddOn)
{
	biomeAddOn = newBiomeAddOn;
}

void Tile::setSpecificBuilding(Building* newBuilding, sf::Vector2i index)
{
	buildings[index.y][index.x] = new BuildingInstance(newBuilding);
}

void Tile::setSpecificBuilding(Building* newBuilding, std::pair <short, short> index)
{
	buildings[index.first][index.second] = new BuildingInstance(newBuilding);
}

void Tile::setSpecificBuilding(Building* newBuilding, short x, short y)
{
	buildings[y][x] = new BuildingInstance(newBuilding);
}

void Tile::deleteBuilding(sf::Vector2i index)
{
	delete buildings[index.y][index.x];
	buildings[index.y][index.x] = nullptr;
}

void Tile::deleteBuilding(std::pair <short, short> index)
{
	delete buildings[index.first][index.second];
	buildings[index.first][index.second] = nullptr;
}

void Tile::deleteBuilding(short x, short y)
{
	delete buildings[y][x];
	buildings[y][x] = nullptr;
}
/*
void Tile::draw(sf::RenderWindow& window) //override
{
	type->draw(window, position);
}

void Tile::draw(sf::RenderTexture& texture)
{
	type->draw(texture, position);
}*/
