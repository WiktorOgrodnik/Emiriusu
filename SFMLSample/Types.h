#pragma once
#ifndef TYPES_H
#define TYPES_H

#include "pch.h"


class Biome 
{
	int id; /// id kafelka
	std::string name; /// nazwa biomu
	sf::Color biomeColor; /// kolor biomu
	float moveCost; /// koszt ruchu na biomie
	float opacity; /// 
	short food; /// jedzenie
	short stone; /// kamieñ
	short wood; /// drewno
	bool canBuildACity; /// Czy mo¿na zbudowaæ miasto
	bool canWalkThru; /// Czy mo¿na przejœæ
	std::string specialStuff; /// Dodatkowe rzeczy

	///Zablokowanie mo¿liwoœci kopiowania
	Biome operator= (const Biome& other);
	Biome(const Biome& other);

public:

	Biome(std::string fileName); /// Konstruktor - przyjmuje nazwê pliku biomu

	///Gettery zmiennych
	std::string getName();
	int getId();
	float getMoveCost();
	short getFood();
	short getStone();
	short getWood();
	bool getCanBuildACity();
	bool getCanWalkThru();
	std::string getSpecialStuff();
	sf::Color* getBiomeColor();

	void setColor(char r, char g, char b, char transparency); /// Ustawia kolor biomu
	
};

class BiomeAddOn
{
public:
};

class Building
{
	std::string name; /// Nazwa budynku
	std::string texture; /// Nazwa tekstury budynku
	std::string districtType; /// Kategora budynku (do dzielnic)
	bool canEdit; /// Czy mo¿na edytowaæ budynek


	///Zablokowanie mo¿liwoœci kopiowania
	Building operator= (const Building& other);
	Building(const Building& other);

public:

	Building(std::string fileName); /// Konstruktor - przyjmuje nazwê pliku budynku

	///Settery
	void setCanEdit(bool canEdit_); 
	void setDistrictType(std::string newDistrictType);

	///Gettery
	std::string getName();
	std::string getTextureId();
	bool getCanEdit();
	std::string getDistrictType();

};


class BuildingInstance : public Object
{
	Building* type; /// Typ budynku
	sf::Texture* texture; /// Tesktura budynku
	sf::RectangleShape body; /// Body budynku
	sf::Vector2f position; /// pierwsza wartoœæ to indeks x, a druga to index y

	Player* owner; /// W³aœciciel (konkretny gracz)

	std::pair <short, short> cityPos; /// Pozycja w mieœcie

	bool locke; /// Zmienna blokady

	void setOwner(Player* newPlayer); /// Ustawia gracza

public:

	~BuildingInstance(); /// Destruktor

	void draw(sf::RenderWindow& window) override; /// witualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u¿ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	BuildingInstance(Building* newType, sf::Vector2f rootPos, std::pair<unsigned, unsigned> additionalPos, Player* player, std::pair <short, short> newCityPos); /// Konstruktor

	///Ustawia/zwraca typ
	void setType(Building* newType);
	Building* getType();

	Player* getOwner(); //zwraca w³aœciela

	void addToDistrict(); /// Dodaj do dzielnicy (ten budynek)
	std::vector <BuildingInstance*> getFriends(); /// Zwraca s¹siadów budynku, które s¹ tej samej kategorii i nale¿¹ do tego samego gracza. Równie¿ na innych miastach.

	void lock(); ///Zablokuj
	void unlock(); ///Odblokuj
	bool getLock(); ///Zwraca stan blokady
};

class Mineral 
{
public:
};

#endif /* TYPES_H */

