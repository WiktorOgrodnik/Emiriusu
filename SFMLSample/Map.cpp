#include "pch.h"

Map::Map(int size)
{
	mapSize = size;
	Engine::getInstance().mapPointer = this;
	newMap();
}

void Map::newMap()
{
	std::vector <std::vector <float>> protoMap;
	std::vector <std::vector <int>> protoBiomes; // zwraca biomy jako inty
	std::vector <std::vector <bool>> protoRivers;
	std::vector <std::vector <bool>> protoMountains;
	std::vector <std::vector <int>> mapInfo; // do podania informacji o mapie wysokosci
	std::vector <std::vector <int>> continents;
	std::vector <std::vector <int>> protoPlayers;

	int numberOfContinents = 0;

	Map::Tiles.resize(mapSize);

	protoMap.resize(mapSize);
	protoPlayers.resize(mapSize);
	protoBiomes.resize(mapSize);
	protoRivers.resize(mapSize);
	protoMountains.resize(mapSize);
	mapInfo.resize(mapSize);
	continents.resize(mapSize);

	for (int i = 0; i < mapSize; i++)
	{
		Tiles[i].resize(mapSize);
		protoPlayers[i].resize(mapSize);
		protoBiomes[i].resize(mapSize);
		protoMountains[i].resize(mapSize);
		mapInfo[i].resize(mapSize);
		protoRivers[i].resize(mapSize);
		protoMap[i].resize(mapSize);
		continents[i].resize(mapSize);
	}

	PerlinNoise::makeHeightMap(protoMap);

	int n = mapSize;
	int c = 0;
	while (n > 0)
	{
		n /= 2;
		c++;
	}
	
	PerlinNoise::GenerateMapInfo(Engine::getInstance().getData().World().getLandPercentage(), Engine::getInstance().getData().World().getMountainsPercentage(), protoMap, mapInfo);
	CelluralAutomata::divideContinents(continents, mapInfo, numberOfContinents); // // kazdemu kontynentowi przypisuje unikalna liczbe
	CelluralAutomata::makeBiomesMap(mapInfo, protoBiomes, 3, 5, 2, 4); // tworzy na polach z grassem 3 rozne biomy (inty od 3 do 5)
	CelluralAutomata::makeMountainsMap(mapInfo, protoMountains, protoRivers, continents, numberOfContinents);
	CelluralAutomata::makeRiversMap(mapInfo, protoRivers, protoMap, continents, numberOfContinents, protoMountains);
	Random::generateStartingPositions(2, mapInfo, protoMountains, protoRivers, protoPlayers);
	for (int i = 0; i < protoPlayers.size(); i++)
	{
		for (int j = 0; j < protoPlayers[i].size(); j++)
		{
			if (protoPlayers[i][j] == 1) test1 = std::make_pair(i, j);
			if (protoPlayers[i][j] == 2) test2 = std::make_pair(i, j);
		}
	}
	for (int i = 0; i < protoMap.size(); i++)
	{
		for (int j = 0; j < protoMap[i].size(); j++)
		{
			if (protoMountains[i][j])
			{
				Tiles[i][j] = new Tile(Engine::getInstance().getData().getBiome("mountains"), sf::Vector2f(i * tileResolution, j * tileResolution));
				
				if (protoRivers[i][j])
				{
					char tempRiverType = 0;
					if (i && (protoRivers[i - 1ll][j] || !mapInfo[i - 1ll][j])) tempRiverType |= (1 << 3); //wylot z góry
					if (j != mapSize - 1 && (protoRivers[i][j + 1ll] || !mapInfo[i][j + 1ll])) tempRiverType |= (1 << 2); //wylot z prawej
					if (i != mapSize - 1 && (protoRivers[i + 1ll][j] || !mapInfo[i + 1ll][j])) tempRiverType |= (1 << 1); //wylot z dołu
					if (j && (protoRivers[i][j - 1ll] || !mapInfo[i][j - 1ll])) tempRiverType |= (1 << 0); //wylot z lewej

					///Losowanie niestandardowych wariantów
					rng::uid = std::uniform_int_distribution<unsigned>(1, 20);
					int r = rng::uid(rng::mt);

					//if (r == 4) tempRiverType |= (1 << 4);
					//else if (r == 5) tempRiverType |= (1 << 5);
					//else if (r == 16) tempRiverType |= (1 << 6);
					//else if (r == 17) tempRiverType |= (1 << 7);

					Tiles[i][j]->setRiver(tempRiverType);
					//std::cerr << "Kafelek: " << i << ", " << j << " ma river type: " << tempRiverType << "\n";
				}
			}
			else
			{
				if (mapInfo[i][j] == 2)
				{
					Tiles[i][j] = new Tile(Engine::getInstance().getData().getBiome("hills"), sf::Vector2f(i * 96, j * 96)); // tutaj mają być hillsy
				}
				else if (mapInfo[i][j] == 0)
				{
					Tiles[i][j] = new Tile(Engine::getInstance().getData().getBiome("water"), sf::Vector2f(i * 96, j * 96));
				}
				else if (protoBiomes[i][j] == 3)
				{
					mapInfo[i][j] = 3;
					Tiles[i][j] = new Tile(Engine::getInstance().getData().getBiome("glade"), sf::Vector2f(i * 96, j * 96));
				}
				else if (protoBiomes[i][j] == 4)
				{
					mapInfo[i][j] = 4;
					Tiles[i][j] = new Tile(Engine::getInstance().getData().getBiome("desert"), sf::Vector2f(i * 96, j * 96));
				}
				else if (protoBiomes[i][j] == 5)
				{
					mapInfo[i][j] = 5;
					Tiles[i][j] = new Tile(Engine::getInstance().getData().getBiome("woods"), sf::Vector2f(i * 96, j * 96));
				}
				if (protoRivers[i][j])
				{
					char tempRiverType = 0;
					if (i && (protoRivers[i - 1][j] || !mapInfo[i - 1][j])) tempRiverType |= (1 << 3); //wylot z góry
					if (j != mapSize - 1 && (protoRivers[i][j + 1] || !mapInfo[i][j + 1])) tempRiverType |= (1 << 2); //wylot z prawej
					if (i != mapSize - 1 && (protoRivers[i + 1][j] || !mapInfo[i + 1][j])) tempRiverType |= (1 << 1); //wylot z dołu
					if (j && (protoRivers[i][j - 1] || !mapInfo[i][j - 1])) tempRiverType |= (1 << 0); //wylot z lewej

					///Losowanie niestandardowych wariantów
					rng::uid = std::uniform_int_distribution<unsigned>(1, 20);
					int r = rng::uid(rng::mt);

					//if (r == 4) tempRiverType |= (1 << 4);
					//else if (r == 5) tempRiverType |= (1 << 5);
					//else if (r == 16) tempRiverType |= (1 << 6);
					//else if (r == 17) tempRiverType |= (1 << 7);

					Tiles[i][j]->setRiver(tempRiverType);
					//std::cerr << "Kafelek: " << i << ", " << j << " ma river type: " << (int)tempRiverType << "\n";
				}
			}
		}
	}

	QuadTree quadTree(mapSize, mapInfo, c + 1);
}

char Map::getMapOverlayData(unsigned x, unsigned y, char level, char type)
{
	if (type == 0)
	{
		if (level) return Tiles[x][y]->getRand();
		return Tiles[x][y]->getType()->getId();
	}
	else if (type == 1)
	{
		if (level) return Tiles[x][y]->getRiverExtra();
		return Tiles[x][y]->getRiver();
	}
	else if (type == 2)
	{
		if (Tiles[x][y]->getSelectable() == nullptr) return 0;
		else
		{
			//if (level) return Tiles[x][y]->getArmy()->getArmyExtra();
			//return Tiles[x][y]->getArmy()->getArmyType();
		}
	}
	else if (type == 3)
	{
		if (Tiles[x][y]->getCity() != nullptr)
		{
			if (level) return 0; // tymczasowo
			return 0; // tymczasowo
		}
	}
}

void Map::setSize(int newSize)
{
	mapSize = newSize;
}

int Map::getSize()
{
	return mapSize;
}

Tile* Map::getTile(unsigned x, unsigned y)
{
	//Log::newLog("Map::getTile: przekazuje dostęp do Tile x = " + std::to_string(x) + " y = " + std::to_string(y));

	if (x > mapSize || y > mapSize)
	{
		Log::newLog("Map::getTile: x i y wykroczyły poza dostęp. Błąd krytyczny.");
		return false;
	}

	return Tiles[x][y];
}

Tile* Map::getTile(sf::Vector2i position) 
{ 
	//Log::newLog("Map::getTile: przekazuje dostęp do Tile x = " + std::to_string(position.x) + " y = " + std::to_string(position.y));

	if (position.x > mapSize || position.y > mapSize)
	{
		Log::newLog("Map::getTile: x i y wykroczyły poza dostęp. Błąd krytyczny.");
		return false;
	}

	return Tiles[position.x][position.y]; 
}
