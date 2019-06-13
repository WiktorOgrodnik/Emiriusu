#pragma once

#include "pch.h"

class Army : public Object, public Selectable
{

private:
	std::vector<Unit*>units;
	float amountOfMovement;
	unsigned unitCount;
	sf::Texture* texture;
	sf::RectangleShape body;
	sf::Vector2u position; /// pierwsza warto�� to indeks x, a druga to index y
	char armyType;
	char armyExtra;

public:

	Army(sf::Vector2u newPosition, Map& map, sf::Texture* newTexture);
	~Army();
	void draw(sf::RenderWindow& window) override; /// wirtualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u�ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	void addUnit(Unit* newUnit);
	void mergeArmies(Army* secondArmy);
	unsigned getNumberOfUnits();
	bool move(sf::Vector2u targetPosition, Map& map);
	Unit* getUnit(unsigned index);
	void setTexture(sf::Texture* newTexture);

	void setPosition(sf::Vector2u newPosition);

	void setArmyType(char newArmyType);

	char getArmyType() { return armyType; }
	char getArmyExtra() { return armyExtra; }
};
