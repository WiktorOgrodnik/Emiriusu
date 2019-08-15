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
	selectable = -1;
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
	selectable = -1;
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
	selectable = -1;
	riverExtra = 0;
	city = nullptr;
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
	selectable = -1;
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
	selectable = -1;
	riverExtra = 0;
	city = nullptr;
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, Player* player)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = nullptr;
	selectable = -1;
	riverExtra = 0;
	createCity(player);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, Player* player)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = nullptr;
	selectable = -1;
	riverExtra = 0;
	createCity(player);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn, Player* player)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = nullptr;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	selectable = -1;
	riverExtra = 0;
	createCity(player);
}

Tile::Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn, Player* player)
{
	rand_ = 0;
	setRand();

	type = newType;
	position = newPosition;
	mineral = newMineral;
	riverType = 0;
	biomeAddOn = newBiomeAddOn;
	selectable = -1;
	riverExtra = 0;
	createCity(player);
}

void Tile::createCity(Player* player)
{
	if (city != nullptr)
	{
		std::string exception = "miasto na kafelku ju¿ istnieje";
		throw exception;
	}

	Log::newLog("Tworzê miasto dla gracza " + player->getNickName());

	city = new City(position, player);
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

void Tile::addSelectable(Selectable* newSelectable)
{
	clickableObjects.push_back(newSelectable);
	selectable = clickableObjects.size() - 1;
}

Selectable* Tile::getSelectable()
{
	if (selectable == -1) return nullptr;
	Selectable* temp = clickableObjects.at(selectable);
	selectable--;
	if (selectable == -1) selectable = clickableObjects.size() - 1;
	return temp;
}

void Tile::ereaseSelectable()
{
	clickableObjects[selectable] = nullptr;
	clickableObjects.erase(clickableObjects.begin() + selectable);
}

void Tile::skipSelectable()
{
	selectable--;
	if (selectable == -1) selectable = clickableObjects.size() - 1;
}

void Tile::setType(Biome* newType)
{
	type = newType;
}

void Tile::setMineral(Mineral* newMineral)
{
	mineral = newMineral;
}

void Tile::setSetOfBuildings(Player* player, std::vector <std::vector<Building*>> newBuildings)
{
	if (city == nullptr) city = new City(position, player, newBuildings);
	else city->setSetOfBuildings(newBuildings);
}

void Tile::setAddOn(BiomeAddOn* newBiomeAddOn)
{
	biomeAddOn = newBiomeAddOn;
}

void Tile::setSpecificBuilding(Player* player, Building* newBuilding, sf::Vector2i index)
{
	if (city == nullptr) city = new City(position, player, newBuilding, index);
	else city->setSpecificBuilding(player, newBuilding, index);
}

void Tile::setSpecificBuilding(Player* player, Building* newBuilding, std::pair <short, short> index)
{
	if (city == nullptr) city = new City(position, player, newBuilding, index);
	else city->setSpecificBuilding(player, newBuilding, index);
}

void Tile::setSpecificBuilding(Player* player, Building* newBuilding, short x, short y)
{
	if (city == nullptr) city = new City(position, player, newBuilding, x, y);
	else city->setSpecificBuilding(player, newBuilding, x, y);
}

void Tile::deleteBuilding(sf::Vector2i index)
{
	if (city == nullptr) Log::newLog("Nie ma nic do usuniêcia!");
	else city->deleteBuilding(index);
}

void Tile::deleteBuilding(std::pair <short, short> index)
{
	if (city == nullptr) Log::newLog("Nie ma nic do usuniêcia!");
	else city->deleteBuilding(index);
}

void Tile::deleteBuilding(short x, short y)
{
	if (city == nullptr) Log::newLog("Nie ma nic do usuniêcia!");
	else city->deleteBuilding(x, y);
}

City* Tile::getCity()
{
	if (city == nullptr)
	{
		std::string exception = "miasto nie istnieje";
		throw exception;
	}
	return city;
}
