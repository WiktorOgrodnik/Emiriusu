#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "pch.h"

class City;
class Army;

class Player
{
private:

	Fraction* fraction; ///Przechowuje informacje o wybranej przez gracza frakcji
	std::string nickName; /// Przechowuje nick gracza

	int playerAdvanceLevel; /// Przechowuje poziom zaawanzowania technicznego gracza
	int AIType; /// Przechowuje typ AI gracza (0 - brak AI)

	std::set <Army*> armies;

	///Zapobiega kopiowaniu
	Player operator= (Player& other){}
	Player(const Player& other){}

public:

	///settery
	void setNickName(std::string _nickName);
	void setAIType(int _AIType);
	void setFraction(Fraction* newFraction);
	void setPlayerAdvanceLevel(int newValue);

	void createCity(sf::Vector2i index);
	void createCity(std::pair <short, short> index);
	void createCity(short x, short y);

	City* getCity(sf::Vector2i index);
	City* getCity(std::pair <short, short> index);
	City* getCity(short x, short y);

	Army* createArmy(sf::Vector2i index, std::string type);
	Army* createArmy(std::pair<short, short> index, std::string type);
	Army* createArmy(short x, short y, std::string type);

	Army* getArmy(Army* army);

	bool checkIfArmy(Army* army);

	///gettery
	std::string getNickName();
	int getAIType();
	Fraction* getFraction();
	int getPlayerAdvanceLevel();
	
	Player();

};

#endif /* PLAYER_H */

