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

