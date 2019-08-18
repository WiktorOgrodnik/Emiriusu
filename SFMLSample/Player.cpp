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
		Log::newLog("Zmienono nick gracza " + nickName + " na " + _nickName);
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

