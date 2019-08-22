#pragma once
#ifndef DATA_H
#define DATA_H

#include "pch.h"
#include "Types.h"

class Settings
{
	float zoom; /// przybli¿enie mapy

	///Zablokowanie mo¿liwoœci kopiowania
	Settings operator= (const Settings& other);
	Settings(const Settings& other);

public:

	Settings(); /// konstruktor
	void setZoom(float newZoom); /// ustawia nowe przybli¿enie mapy (przyjmuje nowe przybli¿enie)
	float getZoom(); /// zwraca obecne przybli¿enie mapy
	void increaseZoom(float val); ///zmienia przybli¿enie mapy o podan¹ wartoœæ
};

class World
{
	int mapSize; /// rozmiar mapy
	float landPercentage; ///  iloœæ l¹du - u³amek
	float mountainsPercentage; /// iloœæ gór - u³amek

	///Zablokowanie mo¿liwoœci kopiowania
	World operator= (const World& other);
	World(const World& other);

public:

	World(); /// konstruktor
	float getLandPercentage(); /// zwraca procent l¹du na mapie
	float getMountainsPercentage(); /// zwraca procent gór na mapie
	int getMapSize();/// zwraca rozmiar mapy

};

class Textures
{
	std::map <std::string, sf::Texture*> textures; /// wszystkie tekstury
	std::map <std::string, sf::Texture*> tileSets; /// wszystkie zestawy tekstur

	void loadTileSets(); /// ³aduje zestawy tekstur do pamiêci
	void loadOtherTextures(); /// ³aduje tekstury do pamiêci

	///Zablokowanie mo¿liwoœci kopiowania
	Textures operator= (const Textures& other);
	Textures(const Textures& other);

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
	std::map <std::string, ArmyPrototype*> armies; /// Przechowuje prototypy armii
	std::map <std::string, Player*> playersMap; /// Przechowuje graczy w mapie
	std::map <BuildingInstance*, District*> districtMap; /// Przechowuje budynki i przypisane do nich dzielnice
	std::set <District*> districts; /// Przechowuje dzielnice (dla Garbage Collectora)
	std::queue <Player*> players; ///Przechowuje graczy w kolejce gry
	std::map <BuildingInstance*, City*> citiesByBuildings; /// Przechowuje budynki i przypisane do nich miasta

	void loadData(); /// ³aduje informacje o lokalizacji plików info
	void loadSelectData(std::string type); /// ³aduje informacje o wskazanej treœci
	void createTypes(); ///tworzy typy danych na podstawie informacji

	void addToDisMap(BuildingInstance* b, District* d); /// Dodaje nowe wartoœci do mapy Dzielnic
	void garbageCollector(); /// Usuwa niepotrzebne dzielnice

	///Zablokowanie mo¿liwoœci kopiowania
	Data operator= (const Data& other);
	Data(const Data& other);

public:

	Data(); /// konstruktor
	~Data() {} /// destruktor

	World& World() { return world; } /// zwraca referencjê na World
	Textures& Textures() { return textures; } /// zwraca referencjê na Textures
	Settings& Settings() { return settings; } /// zwraca referencjê na Settings

	Biome* getBiome(std::string type); /// zwraca dostêp do wskazamego biomu
	Building* getBuilding(std::string type); /// zwraca dostep do wskazanego budynku
	Fraction* getFraction(std::string type); /// zwraca dostêp do wskazanej frakcji
	ArmyPrototype* getArmyPrototype(std::string type); /// zwraca dostêp do wskazanego prototypu armii
	District* getDistrict(BuildingInstance* buildingD); /// zwraca dostep do wskazanej dzielnicy
	City* getCity(BuildingInstance* buildingC); /// zwraca dostep do wskazanego miasta

	Player* getPlayer(std::string name); /// Pozwala uzyskaæ dostêp do konkretnego gracza
	void addPlayer(Player* newPlayer); /// Dodaje nowego gracza (nie mo¿na tu stworztæ gracza, trzeba go stworzyæ wczeœniej)
	bool checkIfPlayer(std::string name); /// Sprawdza, czy gracz o nicku ju¿ istnieje

	void reportBuildingInstance(BuildingInstance* buildingToCity, City* newCity); /// Trzeba tu zg³oœiæ powstanie nowego budynku
	void reportDestructionBuildingInstance(BuildingInstance* toDestroy); /// Nale¿y zg³osiæ zniszczenie budynku
	void addDistrict(BuildingInstance* buildingToDistrict); /// Dodaje wskazany budynek do dzielnicy 
	int getNumberOfDistricts(); /// Uzyskaj liczbê dzielnic
	void refreshDistricts(Player* refreshPlayer); /// Zbuduj wszystkie dzielnice gracza na nowo (podczas usuwania budynku jest wywo³ywana)
	
};

#endif /* DATA_H */

