#include "pch.h"
#include "Player.h"

Player::Player()
{
	playerAdvanceLevel = 1;
	fraction = nullptr;
	AIType = 0;
}

void Player::setNickName(std::string _nickName)
{
	if (!Engine::getInstance().getData().checkIfPlayer(_nickName))
	{
		if (nickName != "") Log::newLog("Zmienono nick gracza " + nickName + " na " + _nickName);
		else Log::newLog("Utworzono gracza o nicku " + _nickName);
		nickName = _nickName;
	}
	else
	{
		std::string exception = "Gracz o nicku " + _nickName + " ju¿ istnieje";
		throw exception;
	}
}

void Player::setAIType(int _AIType)
{
	AIType = _AIType;
}

void Player::setFraction(Fraction* newFraction)
{
	fraction = newFraction;
}

void Player::setPlayerAdvanceLevel(int newValue)
{
	playerAdvanceLevel = newValue;
}

void Player::createCity(sf::Vector2i index)
{
	if (Engine::getInstance().getGlobalMap()->getTile(index)->checkIfCity()) throw "To miejsce jest ju¿ zajête przez inne miasto!";
	Engine::getInstance().getGlobalMap()->getTile(index)->createCity(this);
}

void Player::createCity(std::pair <short, short> index)
{
	if (Engine::getInstance().getGlobalMap()->getTile(index)->checkIfCity()) throw "To miejsce jest ju¿ zajête przez inne miasto!";
	Engine::getInstance().getGlobalMap()->getTile(index)->createCity(this);
}

void Player::createCity(short x, short y)
{
	if (Engine::getInstance().getGlobalMap()->getTile(x, y)->checkIfCity()) throw "To miejsce jest ju¿ zajête przez inne miasto!";
	Engine::getInstance().getGlobalMap()->getTile(x, y)->createCity(this);
}

City* Player::getCity(sf::Vector2i index)
{
	if (Engine::getInstance().getGlobalMap()->getTile(index)->checkIfCity())
	{
		if (Engine::getInstance().getGlobalMap()->getTile(index)->getCity()->getOwner() == this)
		{
			return Engine::getInstance().getGlobalMap()->getTile(index)->getCity();
		}
		else throw "Miasto nie nale¿y do gracza!";
	}
	else throw "Na ¿¹danym przez gracza polu nie ma miasta";
}

City* Player::getCity(std::pair<short, short> index)
{
	if (Engine::getInstance().getGlobalMap()->getTile(index)->checkIfCity())
	{
		if (Engine::getInstance().getGlobalMap()->getTile(index)->getCity()->getOwner() == this)
		{
			return Engine::getInstance().getGlobalMap()->getTile(index)->getCity();
		}
		else throw "Miasto nie nale¿y do gracza!";
	}
	else throw "Na ¿¹danym przez gracza polu nie ma miasta";
}

City* Player::getCity(short x, short y)
{
	if (Engine::getInstance().getGlobalMap()->getTile(x, y)->checkIfCity())
	{
		if (Engine::getInstance().getGlobalMap()->getTile(x, y)->getCity()->getOwner() == this)
		{
			return Engine::getInstance().getGlobalMap()->getTile(x, y)->getCity();
		}
		else throw "Miasto nie nale¿y do gracza!";
	}
	else throw "Na ¿¹danym przez gracza polu nie ma miasta";
}

bool Player::checkIfCity(sf::Vector2i index)
{
	if (Engine::getInstance().getGlobalMap()->getTile(index)->checkIfCity())
	{
		if (Engine::getInstance().getGlobalMap()->getTile(index)->getCity()->getOwner() == this)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool Player::checkIfCity(std::pair <short, short> index)
{
	if (Engine::getInstance().getGlobalMap()->getTile(index)->checkIfCity())
	{
		if (Engine::getInstance().getGlobalMap()->getTile(index)->getCity()->getOwner() == this)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool Player::checkIfCity(short x, short y)
{
	if (Engine::getInstance().getGlobalMap()->getTile(x, y)->checkIfCity())
	{
		if (Engine::getInstance().getGlobalMap()->getTile(x, y)->getCity()->getOwner() == this)
		{
			return true;
		}
		return false;
	}
	return false;
}

void Player::createBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex, std::string type)
{
	if (checkIfCity(cityIndex))
	{
		City* city = getCity(cityIndex);
		if (!(city->existBuilding(buildingIndex)))
		{
			city->setSpecificBuilding(Engine::getInstance().getData().getBuilding(type), buildingIndex);
		}
		else throw "W wybranej pozycji ju¿ le¿y miasto";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::createBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex, std::string type)
{
	if (checkIfCity(cityIndex))
	{
		City* city = getCity(cityIndex);
		if (!(city->existBuilding(buildingIndex)))
		{
			city->setSpecificBuilding(Engine::getInstance().getData().getBuilding(type), buildingIndex);
		}
		else throw "W wybranej pozycji ju¿ le¿y miasto";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::createBuilding(short cityX, short cityY, short buildingX, short buildingY, std::string type)
{
	if (checkIfCity(cityX, cityY))
	{
		City* city = getCity(cityX, cityY);
		if (!(city->existBuilding(buildingX, buildingY)))
		{
			city->setSpecificBuilding(Engine::getInstance().getData().getBuilding(type), buildingX, buildingY);
		}
		else throw "W wybranej pozycji ju¿ le¿y miasto";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::setBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex, std::string type)
{
	if (checkIfCity(cityIndex)) getCity(cityIndex)->setSpecificBuilding(Engine::getInstance().getData().getBuilding(type), buildingIndex);
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::setBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex, std::string type)
{
	if (checkIfCity(cityIndex)) getCity(cityIndex)->setSpecificBuilding(Engine::getInstance().getData().getBuilding(type), buildingIndex);
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::setBuilding(short cityX, short cityY, short buildingX, short buildingY, std::string type)
{
	if (checkIfCity(cityX, cityY)) getCity(cityX, cityY)->setSpecificBuilding(Engine::getInstance().getData().getBuilding(type), buildingX, buildingY);
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::deleteBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex)
{
	if (checkIfCity(cityIndex))
	{
		if (checkIfBuilding(cityIndex, buildingIndex))
		{
			getCity(cityIndex)->deleteBuilding(buildingIndex);
		}
		else throw "Na tym polu nie ma miasta do usuniêcia";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::deleteBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex)
{
	if (checkIfCity(cityIndex))
	{
		if (checkIfBuilding(cityIndex, buildingIndex))
		{
			getCity(cityIndex)->deleteBuilding(buildingIndex);
		}
		else throw "Na tym polu nie ma miasta do usuniêcia";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

void Player::deleteBuilding(short cityX, short cityY, short buildingX, short buildingY)
{
	if (checkIfCity(cityX, cityY))
	{
		if (checkIfBuilding(cityX, cityY, buildingX, buildingY))
		{
			getCity(cityX, cityY)->deleteBuilding(buildingX, buildingY);
		}
		else throw "Na tym polu nie ma miasta do usuniêcia";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

BuildingInstance* Player::getBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex)
{
	if (checkIfCity(cityIndex))
	{
		if (checkIfBuilding(cityIndex, buildingIndex))
		{
			return getCity(cityIndex)->getBuilding(buildingIndex);
		}
		else throw "Na tym polu nie ma budynku!";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

BuildingInstance* Player::getBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex)
{
	if (checkIfCity(cityIndex))
	{
		if (checkIfBuilding(cityIndex, buildingIndex))
		{
			return getCity(cityIndex)->getBuilding(buildingIndex);
		}
		else throw "Na tym polu nie ma budynku!";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

BuildingInstance* Player::getBuilding(short cityX, short cityY, short buildingX, short buildingY)
{
	if (checkIfCity(cityX, cityY))
	{
		if (checkIfBuilding(cityX, cityY, buildingX, buildingY))
		{
			return getCity(cityX, cityY)->getBuilding(buildingX, buildingY);
		}
		else throw "Na tym polu nie ma budynku!";
	}
	else throw "Miasto na kafelku nie istnieje lub nie nale¿y do gracza";
}

bool Player::checkIfBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex)
{
	if (checkIfCity(cityIndex))
	{
		if (getCity(cityIndex)->existBuilding(buildingIndex)) return true;
		return false;
	}
	return false;
}

bool Player::checkIfBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex)
{
	if (checkIfCity(cityIndex))
	{
		if (getCity(cityIndex)->existBuilding(buildingIndex)) return true;
		return false;
	}
	return false;
}

bool Player::checkIfBuilding(short cityX, short cityY, short buildingX, short buildingY)
{
	if (checkIfCity(cityX, cityY))
	{
		if (getCity(cityX, cityY)->existBuilding(buildingX, buildingY)) return true;
		return false;
	}
	return false;
}

Army* Player::createArmy(sf::Vector2i index, std::string type)
{
	Army* tempArmy = new Army(index, Engine::getInstance().getData().getArmyPrototype(type), this);
	armies.emplace(tempArmy);
	return tempArmy;
}

Army* Player::createArmy(std::pair <short, short> index, std::string type)
{
	Army* tempArmy = new Army(index, Engine::getInstance().getData().getArmyPrototype(type), this);
	armies.emplace(tempArmy);
	return tempArmy;
}

Army* Player::createArmy(short x, short y, std::string type)
{
	Army* tempArmy = new Army(x, y, Engine::getInstance().getData().getArmyPrototype(type), this);
	armies.emplace(tempArmy);
	return tempArmy;
}

Army* Player::getArmy(Army* army)
{
	auto it = armies.find(army);
	if (it == armies.end()) throw "Nie znaleziono takiej armii w klasie gracza!";
	return *it;
}

bool Player::checkIfArmy(Army* army)
{
	auto it = armies.find(army);
	if (it == armies.end()) return false;
	return true;
}

std::string Player::getNickName()
{
	return nickName;
}

int Player::getAIType()
{
	return AIType;
}

Fraction* Player::getFraction()
{
	return fraction;
}

int Player::getPlayerAdvanceLevel()
{
	return playerAdvanceLevel;
}

