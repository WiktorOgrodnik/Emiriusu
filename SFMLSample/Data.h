#pragma once
#ifndef DATA_H
#define DATA_H

#include "pch.h"
#include "Types.h"

class Settings
{
	float zoom; /// przybli¿enie mapy

public:

	Settings(); /// konstruktor
	void setZoom(float newZoom); /// ustawia nowe przybli¿enie mapy (przyjmuje nowe przybli¿enie)
	float getZoom() { return zoom; } /// zwraca obecne przybli¿enie mapy
	void increaseZoom(float val); ///zmienia przybli¿enie mapy o podan¹ wartoœæ
};

class World
{
	int mapSize; /// rozmiar mapy
	float landPercentage; ///  iloœæ l¹du - u³amek
	float mountainsPercentage; /// iloœæ gór - u³amek

public:

	World(); /// konstruktor
	float getLandPercentage() { return landPercentage; } /// zwraca procent l¹du na mapie
	float getMountainsPercentage() { return mountainsPercentage; } /// zwraca procent gór na mapie
	int getMapSize() { return mapSize; } /// zwraca rozmiar mapy

};

class Textures
{
	std::map <std::string, sf::Texture*> textures; /// wszystkie tekstury
	std::map <std::string, sf::Texture*> tileSets; /// wszystkie zestawy tekstur
	std::map <std::string, std::map <std::string, sf::Texture*>> fractionTextures; /// wszystkie tekstury dla stylów frakcji

	void loadTileSets(); /// ³aduje zestawy tekstur do pamiêci
	void loadOtherTextures(); /// ³aduje tekstury do pamiêci
	void loadFractionTextures(); /// ³aduje tekstury dla stylów frakcji do pamiêci

public:

	Textures(); /// konstruktor
	sf::Texture* getTileSet (std::string name); /// zwraca wskaŸnik na tileSet 
	sf::Texture* getTexture (std::string name); /// zwraca wskaŸnik na teksturê
	sf::Texture* getFractionTexture(Fraction* fraction, std::string name); /// zwraca wskaŸnik na tekturê stylów frakcji
	void clearTextures(); /// usuwa wszystkie tekstury z pamiêci
};

class Data
{
	///Tworzenie wszystkich klas przechowuj¹cych dane
	World world; /// Przechowuje informacje dotycz¹ce œwiata
	Textures textures; /// Przechowuje tekstury
	Settings settings; /// Przechowuje ustawienia gry

	std::map<std::string, std::map <std::string, std::string>> datas; /// Przechowuje informacje o typach
	std::map <std::string, Biome*> biomes; /// Przechowuje gotowe biomy
	std::map <std::string, Building*> buildings; /// Przechowuje gotowe budynki (pierwowzory)
	std::map <std::string, Fraction*> fractions; /// Przechowuje frakcje
	std::map <std::string, Player*> playersMap; /// Przechowuje graczy w mapie
	std::map <BuildingInstance*, District*> districtMap;
	std::set <District*> districts;
	std::queue <Player*> players; ///Przechowuje graczy w kolejce gry
	std::map <BuildingInstance*, City*> citiesByBuildings;

	void loadData(); /// ³aduje informacje o lokalizacji plików info
	void loadSelectData(std::string type); /// ³aduje informacje o wskazanej treœci
	void createTypes(); ///tworzy typy danych na podstawie informacji

	void addToDisMap(BuildingInstance* b, District* d);
	void garbageCollector(bool all);

public:

	Data(); /// konstruktor
	~Data() {} /// destruktor

	World& World() { return world; } /// zwraca referencjê na World_
	Textures& Textures() { return textures; } /// zwraca referencjê na Textures_
	Settings& Settings() { return settings; } /// zwraca referencjê na Settings_

	Biome* getBiome(std::string type); /// zwraca dostêp do wskazamego biomu
	Building* getBuilding(std::string type); /// zwraca dostep do wskazanego budynku
	Fraction* getFraction(std::string type); /// zwraca dostêp do wskazanej frakcji
	District* getDistrict(BuildingInstance* buildingD);
	City* getCity(BuildingInstance* buildingC);

	Player* getPlayer(std::string name); /// Pozwala u¿yskaæ dostêp do konkretnego gracza
	void addPlayer(Player* newPlayer); /// Dodaje nowego gracza (nie mo¿na tu stworztæ gracza, trzeba go stworzyæ wczesniej)
	bool checkIfPlayer(std::string name); /// Sprawdza, czy gracz o nicku ju¿ istnieje

	void reportBuildingInstance(BuildingInstance* buildingToCity, City* newCity);
	void reportDestructionBuildingInstance(BuildingInstance* toDestroy);
	void addDistrict(BuildingInstance* buildingToDistrict);
	int getNumberOfDistricts();
	void refreshDistricts();
	
};

#endif /* DATA_H */

