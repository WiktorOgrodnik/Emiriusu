#pragma once
#ifndef CITY_H
#define CITY_H

#include "pch.h"


class City : public Object, public Selectable
{
	std::vector <std::vector <BuildingInstance*>> buildings; /// Wektor budynków
	sf::Texture* texture;
	sf::RectangleShape body;
	sf::Vector2f position; /// pierwsza wartoœæ to indeks x, a druga to index y
	char cityType;
	char cityExtra;


public:

	City(sf::Vector2f newPosition, sf::Texture* newTexture);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, std::vector <std::vector <Building*>> setOfBuildings);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, sf::Vector2i index);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, std::pair<short, short> index);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, short x, short y);

	void draw(sf::RenderWindow& window) override; /// witualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u¿ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	void setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings);
	
	void setSpecificBuilding(Building* building, sf::Vector2i index);
	void setSpecificBuilding(Building* building, std::pair<short, short> index);
	void setSpecificBuilding(Building* building, short x, short y);

	void deleteBuilding(sf::Vector2i index);
	void deleteBuilding(std::pair <short, short> index);
	void deleteBuilding(short x, short y);

	BuildingInstance* getBuilding(sf::Vector2i index) { return buildings[index.x][index.y]; }
	BuildingInstance* getBuilding(std::pair<short, short> index) { return buildings[index.first][index.second]; }
	BuildingInstance* getBuilding(short x, short y) { return buildings[x][y]; }

	Function* onSelect() override;
	Function* onClick() override;
	Function* onDeselect() override;

};

#endif /*CITY_H*/

