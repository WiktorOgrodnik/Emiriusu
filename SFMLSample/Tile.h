#pragma once
#ifndef TILE_H
#define TILE_H

#include "pch.h"

class Tile
{
	Biome* type; /// typ biomu
	BiomeAddOn* biomeAddOn; /// dodatek do biomu (niepotrzebne)
	Mineral* mineral; /// minera³ 
	int selectable; /// obiekt klikalny 
	City* city; /// miasto

	std::vector <Selectable*> clickableObjects; ///strumieñ obiektów klikalnych (armie, miasto, inne obiekty z którymi mo¿na wchodziæ w interakcje)

	sf::Vector2f position; /// pozycja kafelka
	char riverType; /// typ rzeki (0 - brak)
	char riverExtra; /// czy dodatkowy zawijas rzeki?
	int rand_; /// losowy pod typ biomu

	void setPosition(sf::Vector2f newPosition); /// ustawia pozycjê (nie u¿ywaæ)
	void setPosition(float x, float y); /// ustawia pozycjê (nie u¿ywaæ)
	void setRand(); /// Tworzy losow¹ wartoœæ (dla losowych kafelków)

public:

	Tile(Biome* newType, sf::Vector2f newPosition); /// Konstruktory (przyjmuj¹ ró¿ne wartoœci - opisane wy¿ej)
	Tile(Biome* newType, sf::Vector2f newPosition, char riverType_);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral);
	Tile(Biome* newType, sf::Vector2f newPosition, BiomeAddOn* newBiomeAddOn);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, BiomeAddOn* newBiomeAddOn);
	Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, Player* player);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, Player* player);
	Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn, Player* player);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn, Player* player);

	void setCity(City* newCity); /// ustawia nowe miasto
	void setType(Biome* newType); /// ustawia typ kafelka (przyjmuje nowy typ kafelka)
	void setMineral(Mineral* newMineral); /// ustawia minera³
	void setSetOfBuildings(Player* player, std::vector <std::vector <Building*>> newBuildings); /// ustawia zestaw budynków
	void setAddOn(BiomeAddOn* newBiomeAddOn); /// ustawia biomeaddon

	void setRiver(char riverType_); /// ustaw typ rzeki (instrukcja u¿ycia -> map.cpp)
	char getRiver(); /// pobierz typ rzeki
	char getRiverExtra(); /// zwraca info o dodatkowym zawijasie rzeki

	void addSelectable(Selectable* newArmy); /// ustawia na kafelku obiekt klasy selectable
	Selectable* getSelectable(); /// zwraca obiekt klasy selectable
	void ereaseSelectable(); /// usuwa obecnie wybrany selectable
	void skipSelectable(); /// przechodzi do nastêpnego obiektu klikalnego

	void setSpecificBuilding(Player* player, Building* newBuilding, sf::Vector2i index); /// ustaw nowy budynek na konkretnym polu z uwzglednieniem gracza
	void setSpecificBuilding(Player* player, Building* newBuilding, std::pair <short, short> index);
	void setSpecificBuilding(Player* player, Building* newBuilding, short x, short y);

	void deleteBuilding(sf::Vector2i index); /// usuñ konkretny budynek
	void deleteBuilding(std::pair <short, short>);
	void deleteBuilding(short x, short y);

	sf::Vector2f getPosition(); /// zwraca pozycjê kafelka
	Biome* getType(); /// zwraca typ kafelka
	int getRand(); /// zwraca losowy podtyp kafelka
	City* getCity(); /// zwraca miasto
	bool checkIfCity(); /// Zwraca true kiedy miasto istnieje
	void createCity(Player* setPlayer); /// tworzy nowe miasto dla gracza

	BuildingInstance* getBuilding(sf::Vector2i index); /// funkcje zwracaj¹ konkretne budynki
	BuildingInstance* getBuilding(std::pair <short, short> index);
	BuildingInstance* getBuilding(short x, short y);

	///SprawdŸ czy istnieje budynek
	bool existBuilding(sf::Vector2i index);
	bool existBuilding(std::pair <short, short> index);
	bool existBuilding(short x, short y);
};

#endif /* TILE_H */

