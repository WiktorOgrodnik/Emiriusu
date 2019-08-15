#pragma once
#ifndef CITY_H
#define CITY_H

#include "pch.h"


class City : public Object, public Selectable
{
	std::vector <std::vector <BuildingInstance*>> buildings; /// Wektor budynków
	sf::Texture* texture; /// Przechowuje teksture miasta
	sf::RectangleShape body; /// Przechowuje kszta³ miasta
	sf::Vector2f position; /// pierwsza wartoœæ to indeks x, a druga to index y
	char cityType; /// Typ miasta (nie u¿ywane)
	char cityExtra; /// nie u¿ywane


public:

	/// Konstruktory (przyjmuj¹ ró¿ne wartoœci)
	City(sf::Vector2f newPosition, sf::Texture* newTexture);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, std::vector <std::vector <Building*>> setOfBuildings);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, sf::Vector2i index);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, std::pair<short, short> index);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, short x, short y);

	void draw(sf::RenderWindow& window) override; /// witualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u¿ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	void setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings); /// Pozwala ustawiæ gotowy zestaw budynków w mieœcie
	
	///NIE U¯YWAÆ Funkcje pozwalaj¹ budowaæ budynki w mieœcie
	void setSpecificBuilding(Building* building, sf::Vector2i index);
	void setSpecificBuilding(Building* building, std::pair<short, short> index);
	void setSpecificBuilding(Building* building, short x, short y);

	///Funkcje pozwalaj¹ budowaæ budynki w mieœcie dla gracza
	void setSpecificBuildingForPlayer(Player* player, Building* building, sf::Vector2i index);
	void setSpecificBuildingForPlayer(Player* player, Building* building, std::pair<short, short> index);
	void setSpecificBuildingForPlayer(Player* player, Building* building, short x, short y);

	///Usuwanie budynków
	void deleteBuilding(sf::Vector2i index);
	void deleteBuilding(std::pair <short, short> index);
	void deleteBuilding(short x, short y);

	///Zwraca dostep do konkretnego budynku
	BuildingInstance* getBuilding(sf::Vector2i index) { return buildings[index.x][index.y]; }
	BuildingInstance* getBuilding(std::pair<short, short> index) { return buildings[index.first][index.second]; }
	BuildingInstance* getBuilding(short x, short y) { return buildings[x][y]; }

	///Funkcje zwi¹zne z zaznaczaniem
	Function* onSelect() override;
	Function* onClick() override;
	Function* onDeselect() override;

};

#endif /*CITY_H*/

