#pragma once

#include "pch.h"

class Map;

class ArmyPrototype
{
private:
	std::string name;
	std::string texture;
	float defaultAmmountOfMovement;

public:

	ArmyPrototype(std::string fileName);

	std::string getName();
	std::string getTexture();
	float getAmmountOfMovement();

	void setName(std::string newName);
	void setTexture(std::string newTexture);
	void setAmmountOfMovement(int newValue);
};

class Army : public Object, public Selectable
{
private:

	Player* owner;
	ArmyPrototype* type;

	std::vector<Unit*>units;
	float amountOfMovement;
	unsigned unitCount;
	sf::Texture* texture;
	sf::RectangleShape body;
	sf::Vector2i position; /// pierwsza wartoœæ to indeks x, a druga to index y
	std::vector<std::vector<float>> movesData;
	char armyType;
	char armyExtra;

public:

	Army(sf::Vector2i newPosition, ArmyPrototype* newType, Player* player);
	Army(std::pair<short, short> newPosition, ArmyPrototype* newType, Player* player);
	Army(short x, short y, ArmyPrototype* newType, Player* player);

	~Army();
	void draw(sf::RenderWindow& window) override; /// wirtualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u¿ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	void addUnit(Unit* newUnit);
	void mergeArmies(Army* secondArmy);
	unsigned getNumberOfUnits();
	bool move(sf::Vector2i targetPosition, Map& map);
	Unit* getUnit(unsigned index);
	void setTexture(sf::Texture* newTexture);

	void setPosition(sf::Vector2i newPosition);

	void setArmyType(char newArmyType);

	char getArmyType() { return armyType; }
	char getArmyExtra() { return armyExtra; }
	sf::Vector2i getPosition() { return position; }

	Function* onSelect() override;
	Function* onClick() override;
	Function* onDeselect() override;

	void setOwner(Player* player);
	Player* getOwner();

	void setType(ArmyPrototype*);
	ArmyPrototype* getType();

};

