#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "pch.h"

class Player
{
private:

	Fraction* fraction; ///Przechowuje informacje o wybranej przez gracza frakcji
	std::string nickName; /// Przechowuje nick gracza

	int playerAdvanceLevel; /// Przechowuje poziom zaawanzowania technicznego gracza
	int AIType; /// Przechowuje typ AI gracza (0 - brak AI)

public:

	///settery
	void setNickName(std::string _nickName);
	void setAIType(int _AIType);
	void setFraction(Fraction* newFraction);
	void setPlayerAdvanceLevel(int newValue);

	///gettery
	std::string getNickName();
	int getAIType();
	Fraction* getFraction();
	int getPlayerAdvanceLevel();
	
	Player();

};

#endif /* PLAYER_H */

