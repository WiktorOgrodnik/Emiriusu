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

	type = newType;
	position = newPosition;
	riverType = 0;
	mineral = nullptr;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = nullptr;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, char riverType_)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	riverType = riverType_;
	mineral = nullptr;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = nullptr;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral)
{
	rand_ = 0;
	setRand();
	
	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = nullptr;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = new City(newBuildings);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = nullptr;
	army = nullptr;
	riverExtra = 0;
	city = new City(newBuildings);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = nullptr;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = nullptr;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = new City(newBuildings);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	army = nullptr;
	riverExtra = 0;
	city = new City(newBuildings);
}

void Tile::setCity(City* newCity)
{
	city = newCity;
}

void Tile::setRiver(char riverType_)
{
	if (riverType_ & (1 << 0)) riverType |= (1 << 0);
	if (riverType_ & (1 << 1)) riverType |= (1 << 1);
	if (riverType_ & (1 << 2)) riverType |= (1 << 2);
	if (riverType_ & (1 << 3)) riverType |= (1 << 3);
	if (riverType_ & (1 << 4)) riverExtra = 1;
	else if (riverType_ & (1 << 5)) riverExtra = 2;
	else if (riverType_ & (1 << 6)) riverExtra = 3;
	else if (riverType_ & (1 << 7)) riverExtra = 4;
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
	if (city == nullptr) city = new City(newBuildings);
	else city->setSetOfBuildings(newBuildings);
}

void Tile::setAddOn(BiomeAddOn* newBiomeAddOn)
{
	biomeAddOn = newBiomeAddOn;
}

void Tile::setSpecificBuilding(Building* newBuilding, sf::Vector2i index)
{
	if (city == nullptr) city = new City(newBuilding, index);
	else city->setSpecificBuilding(newBuilding, index);
}

void Tile::setSpecificBuilding(Building* newBuilding, std::pair <short, short> index)
{
	if (city == nullptr) city = new City(newBuilding, index);
	else city->setSpecificBuilding(newBuilding, index);
}

void Tile::setSpecificBuilding(Building* newBuilding, short x, short y)
{
	if (city == nullptr) city = new City(newBuilding, x, y);
	else city->setSpecificBuilding(newBuilding, x, y);
}

void Tile::deleteBuilding(sf::Vector2i index)
{
	if (city == nullptr) std::cerr << "Nie ma nic do usuniêcia!\n";
	else city->deleteBuilding(index);
}

void Tile::deleteBuilding(std::pair <short, short> index)
{
	if (city == nullptr) std::cerr << "Nie ma nic do usuniêcia!\n";
	else city->deleteBuilding(index);
}

void Tile::deleteBuilding(short x, short y)
{
	if (city == nullptr) std::cerr << "Nie ma nic do usuniêcia!\n";
	else city->deleteBuilding(x, y);
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
