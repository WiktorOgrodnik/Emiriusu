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
	void increaseZoom(float val); ///zmienia przybli¿enie mapyo podan¹ wartoœæ
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

	void loadTileSets(); /// ³aduje zestawy tekstur do pamiêci
	void loadOtherTextures(); /// ³aduje tekstury do pamiêci

public:

	Textures(); /// konstruktor
	sf::Texture* getTileSet (std::string name); /// zwraca wskaŸnik na tileSet 
	sf::Texture* getTexture (std::string name); /// zwraca wskaŸnik na teksturê
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

	void loadData(); /// ³aduje informacje o lokalizacji plików info
	void loadSelectData(std::string type); /// ³aduje informacje o wskazanej treœci
	void createTypes(); ///tworzy typy danych na podstawie informacji

	//Funkcje przestarza³e lub nieu¿ywane
	std::map <std::string, std::string> biomeDatas; /// Przechowuje informacje o biomach
	Building* riverPlaceholder; /// Placeholder rzeka
	BuildingInstance* riverPlaceholderInstance; /// Placeholder rzeka - instancja

	void loadBiomeData(); /// ³aduje informacje o biomach (depracted)
	void loadRiverPlaceholder(); ///³aduje budynek-rzeka (tymczasowe)

public:

	Data(); /// konstruktor
	~Data() {} /// destruktor

	World& World() { return world; } /// zwraca referencjê na World_
	Textures& Textures() { return textures; } /// zwraca referencjê na Textures_
	Settings& Settings() { return settings; } /// zwraca referencjê na Settings_

	Biome* getBiome(std::string type); /// zwraca dostêp do wskazamego biomu
	Building* getBuilding(std::string type); /// zwraca dostep do wskazanego budynku


	BuildingInstance* getRiverPlaceholderInstance() { return riverPlaceholderInstance; } /// zwraca wskaŸnik na bloker budynków
};

#endif /* DATA_H */

