#pragma once
#ifndef TILE_H
#define TILE_H

#include "pch.h"

class Tile //: public Object
{
	Biome* type; /// typ biomu
	BiomeAddOn* biomeAddOn; /// dodatek do biomu (niepotrzebne)
	Mineral* mineral; /// minera³ 
	Selectable* army; /// armia
	City* city; /// miasto

	std::vector <Selectable*> clickableObjects; ///strumieñ obiektów klikalnych (armie, miasto, inne obiekty z którymi mo¿na wchodziæ w interakcje)

	sf::Vector2f position; /// pozycja kafelka
	//std::vector <std::vector <BuildingInstance*>> buildings; /// Przechowuje budynki (do viktusa - no weŸ no to zrób ej)
	char riverType; /// typ rzeki (0 - brak)
	char riverExtra; /// czy dodatkowy zawijas rzeki?
	int rand_; /// losowy pod typ biomu

	void setPosition(sf::Vector2f newPosition); /// ustawia pozycjê (nie u¿ywaæ)
	void setPosition(float x, float y); /// ustawia pozycjê (nie u¿ywaæ)
	void setRand();

public:

	Tile(Biome* newType, sf::Vector2f newPosition); /// Konstruktory rzeki (przyjmuj¹ ró¿ne wartoœci - opisane wy¿ej)
	Tile(Biome* newType, sf::Vector2f newPosition, char riverType_);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral);
	Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings);
	Tile(Biome* newType, sf::Vector2f newPosition, BiomeAddOn* newBiomeAddOn);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, BiomeAddOn* newBiomeAddOn);
	Tile(Biome* newType, sf::Vector2f newPosition, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn);
	Tile(Biome* newType, sf::Vector2f newPosition, Mineral* newMineral, std::vector <std::vector<Building*>> newBuildings, BiomeAddOn* newBiomeAddOn);

	void setCity(City* newCity); /// ustawia nowe miasto
	void setType(Biome* newType); /// ustawia typ kafelka (przyjmuje nowy typ kafelka)
	void setMineral(Mineral* newMineral); /// ustawia minera³
	void setSetOfBuildings(std::vector <std::vector <Building*>> newBuildings); /// ustawia zestaw budynkó
	void setAddOn(BiomeAddOn* newBiomeAddOn); /// ustawia biomeaddon

	void setRiver(char riverType_); /// ustaw typ rzeki (instrukcja u¿ycia -> map.cpp)
	char getRiver() { return riverType; } /// pobierz typ rzeki
	char getRiverExtra() { return riverExtra; } /// zwraca info o dodatkowym zawijasie rzeki

	void setArmy(Selectable* newArmy); /// ustawia na kafelku obiekt klasy army
	Selectable* getArmy() { return army; } /// zwraca obiekt klasy army

	void setSpecificBuilding(Building* newBuilding, sf::Vector2i index); /// ustaw nowy budynek na konkretnym polu
	void setSpecificBuilding(Building* newBuilding, std::pair <short, short> index);
	void setSpecificBuilding(Building* newBuilding, short x, short y);

	void deleteBuilding(sf::Vector2i index); /// usuñ konkretny budynek
	void deleteBuilding(std::pair <short, short>);
	void deleteBuilding(short x, short y);

	sf::Vector2f getPosition() { return position; } /// zwraca pozycjê kafelka
	Biome* getType() { return type; } /// zwraca typ kafelka
	int getRand() { return rand_; } /// zwraca losowy podtyp kafelka
	City* getCity() { return city; } /// zwraca miasto
	BuildingInstance* getBuilding(sf::Vector2i index) { return city->getBuilding(index); } /// funkcje zwracaj¹ konkretne budynki
	BuildingInstance* getBuilding(std::pair <short, short> index) { return city->getBuilding(index);}
	BuildingInstance* getBuilding(short x, short y) { return city->getBuilding(x, y);}

	//void draw(sf::RenderWindow & window) override; /// rysuje kafelek na ekranie (przyjmuje okno gry)
	//void draw(sf::RenderWindow& window, sf::View& view, float zoom) override { draw(window); }  /// rysuje kafelek na ekranie
	//void draw(sf::RenderTexture& texture) override;
};

#endif /* TILE_H */

