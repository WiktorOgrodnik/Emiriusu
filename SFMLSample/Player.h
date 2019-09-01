#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "pch.h"

class City;
class Army;
class BuildingInstance;

class Player
{
private:

	Fraction* fraction; ///Przechowuje informacje o wybranej przez gracza frakcji
	std::string nickName; /// Przechowuje nick gracza

	int playerAdvanceLevel; /// Przechowuje poziom zaawanzowania technicznego gracza
	int AIType; /// Przechowuje typ AI gracza (0 - brak AI)

	std::set <Army*> armies;

	///Zapobiega kopiowaniu
	Player operator= (Player& other);
	Player(const Player& other);

public:

	Player();

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

	///Stwórz miasto
	void createCity(sf::Vector2i index);
	void createCity(std::pair <short, short> index);
	void createCity(short x, short y);

	///Uzyskaj dostep do miasta (tego gracza
	City* getCity(sf::Vector2i index);
	City* getCity(std::pair <short, short> index);
	City* getCity(short x, short y);

	///SprawdŸ czy jest miasto tego gracza
	bool checkIfCity(sf::Vector2i index);
	bool checkIfCity(std::pair <short, short> index);
	bool checkIfCity(short x, short y);

	///Tworzy budynek, w wypadku gdy pole jest zajête zg³asza wyj¹tek
	void createBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex, std::string type);
	void createBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex, std::string type);
	void createBuilding(short cityX, short cityY, short buildingX, short buildingY, std::string type);

	///Tworzy budynek, w wypadku gdy pole jest zajête nadpisuje je (mniej bezpieczne)
	void setBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex, std::string type);
	void setBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex, std::string type);
	void setBuilding(short cityX, short cityY, short buildingX, short buildingY, std::string type);

	///Usuwa budynek
	void deleteBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex);
	void deleteBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex);
	void deleteBuilding(short cityX, short cityY, short buildingX, short buildingY);

	///Zwraca dostep do budynku
	BuildingInstance* getBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex);
	BuildingInstance* getBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex);
	BuildingInstance* getBuilding(short cityX, short cityY, short buildingX, short buildingY);

	///Sprawdza czy na polu jest budynek nale¿¹cy do gracza
	bool checkIfBuilding(sf::Vector2i cityIndex, sf::Vector2i buildingIndex);
	bool checkIfBuilding(std::pair<short, short> cityIndex, std::pair<short, short> buildingIndex);
	bool checkIfBuilding(short cityX, short cityY, short buildingX, short buildingY);

	///Tworzy armiê na okreslonym polu
	Army* createArmy(sf::Vector2i index, std::string type);
	Army* createArmy(std::pair<short, short> index, std::string type);
	Army* createArmy(short x, short y, std::string type);

	///Zwraca armiê nale¿¹c¹ do gracza
	Army* getArmy(Army* army);

	///Sprawdza czy armia nale¿y do gracza
	bool checkIfArmy(Army* army);

};

#endif /* PLAYER_H */

