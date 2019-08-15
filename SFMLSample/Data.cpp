#include "pch.h"

Settings::Settings()
{
	setZoom(1.0f);
}

void Settings::setZoom(float newZoom)
{
	zoom = newZoom;
	zoom = std::max(1.0f, zoom);
	//Engine::getInstance().getGameScreen().zoom(zoom);
}

void Settings::increaseZoom(const float val)
{
	zoom = zoom + zoom*val;
	zoom = std::max(0.0f, zoom);
	Engine::getInstance().getGameScreen().zoom(1+val);
}

World::World()
{
	///Przypisanie tymczasowe
	mapSize = 100;
	landPercentage = 0.3147f;
	mountainsPercentage = 0.08f;
}

Textures::Textures()
{
	loadTileSets();
	loadOtherTextures();
	loadFractionTextures();
}

void Textures::loadOtherTextures()
{
	std::fstream textureInfoFile;
	const std::string textureInfoFileName = "textures/other.txt";
	std::string tempText, tempText2;

	textureInfoFile.open(textureInfoFileName, std::ios::in);
	if (!textureInfoFile.good()) Log::newLog("Nie uda³o siê odczytaæ pliku: " + textureInfoFileName);
	else
	{
		while (!textureInfoFile.eof())
		{
			std::getline(textureInfoFile, tempText);
			std::getline(textureInfoFile, tempText2);

			sf::Texture* tempTexture = new sf::Texture;
			tempTexture->loadFromFile(tempText2);
			textures.insert(std::make_pair(tempText, tempTexture));
		}
	}
}

void Textures::loadFractionTextures()
{
	Log::newLog("Rozpoczynam ³adowanie tekstur stylów");

	std::fstream fractionInfoFile;
	std::string fractionInfoFileName = "textures/style.txt";
	std::string tempText, tempText2;

	fractionInfoFile.open(fractionInfoFileName, std::ios::in);
	if (!fractionInfoFile.good()) Log::newLog("Nie uda³o siê otworzyæ pliku: " + fractionInfoFileName);
	else
	{
		while (!fractionInfoFile.eof())
		{
			std::getline(fractionInfoFile, tempText);
			std::getline(fractionInfoFile, tempText2);

			std::fstream styleInfoFile;
			std::string styleInfoFileName = tempText2;
			std::string tempText3, tempText4;

			std::map<std::string, sf::Texture*> tempMap;

			Log::newLog("£aduje tekstury dla stylu: " + tempText);

			styleInfoFile.open(styleInfoFileName, std::ios::in);
			if (!styleInfoFile.good()) Log::newLog("Nie uda³o siê otworzyæ pliku: " + styleInfoFileName);
			else
			{
				while (!styleInfoFile.eof())
				{
					std::getline(styleInfoFile, tempText3);
					std::getline(styleInfoFile, tempText4);

					sf::Texture* tempTexture = new sf::Texture;
					tempTexture->loadFromFile(tempText4);
					Log::newLog("£aduje teksturê o nazwie: " + tempText3);
					tempMap.emplace(std::make_pair(tempText3, tempTexture));
				}

				styleInfoFile.close();
			}

			fractionTextures.emplace(std::make_pair(tempText, tempMap));
		}
		fractionInfoFile.close();
	}
}

void Textures::loadTileSets()
{
	std::fstream textureInfoFile;
	const std::string textureInfoFileName = "textureInfo.txt";
	std::string tempText, tempText2;
	std::queue <std::string> fileQueue;

	textureInfoFile.open(textureInfoFileName, std::ios::in);

	if (!textureInfoFile.good()) Log::newLog("Nie uda³o siê odczytaæ pliku: " + textureInfoFileName);
	else
	{
		while (!textureInfoFile.eof())
		{
			std::getline(textureInfoFile, tempText);
			std::getline(textureInfoFile, tempText2);

			fileQueue.push(tempText2);

			tileSets[tempText] = new sf::Texture;
		}

		textureInfoFile.close();

		std::map <std::string, sf::Texture*>::iterator it = tileSets.begin();

		while (!fileQueue.empty())
		{
			int x, y, vcount = 2, numberOfTextures = 0;
			bool varaints = false;
			sf::Texture tempTexture;

			tempText2 = fileQueue.front();
			fileQueue.pop();

			textureInfoFile.open(tempText2, std::ios::in);

			if (!textureInfoFile.good()) Log::newLog("Nie uda³o siê za³adowaæ pliku " + tempText2);
			else
			{
				Log::newLog("Uda³o siê za³adowaæ plik " + tempText2);
				sf::Texture* tileSet = it->second;

				std::getline(textureInfoFile, tempText);
				x = stringToInt(tempText);
				std::getline(textureInfoFile, tempText);
				y = stringToInt(tempText);

				tileSet->create(x * tileResolution, y * tileResolution);

				for (int i = 0; i < x * y + 1; i++)
				{
					std::getline(textureInfoFile, tempText);

					if (tempText == "variants")
					{
						varaints = true;
						numberOfTextures = 0;
					}

					if (!varaints)
					{
						if (!tempTexture.loadFromFile(tempText)) Log::newLog("Nie uda³o siê za³adowaæ tekstury " + tempText);
						
						tileSet->update(tempTexture, tileResolution * numberOfTextures, 0);
						numberOfTextures++;
					}
					else if (tempText != "variants")
					{
						if (!tempTexture.loadFromFile(tempText)) Log::newLog ("Nie uda³o siê za³adowaæ tekstury " + tempText);
						
						tileSet->update(tempTexture, tileResolution * numberOfTextures, tileResolution * (vcount - 1));

						if (vcount == y)
						{
							vcount = 2;
							numberOfTextures++;
						}
						else vcount++;
					}
				}
				it++;
				textureInfoFile.close();
			}
		}
	}
}

sf::Texture* Textures::getTileSet(std::string name)
{
	std::map <std::string, sf::Texture*>::iterator it = tileSets.find(name);
	if (it == tileSets.end()) throw "nie znaleziono zestawu tekstur: " + name;
	return it->second;
}

sf::Texture* Textures::getTexture(std::string name)
{
	std::map <std::string, sf::Texture*>::iterator it = textures.find(name);
	if (it == textures.end()) throw "nie znaleziono tekstury: " + name;
	return it->second;
}

sf::Texture* Textures::getFractionTexture(Fraction* fraction, std::string name)
{
	auto it = fractionTextures.find(fraction->getFractionStyle());
	if (it == fractionTextures.end()) throw "nie znaleziono ¿adnych tekstur dla stylu: " + fraction->getFractionStyle();
	auto jt = it->second.find(name);
	if (jt == it->second.end()) throw "nie znaleziono tekstury: " + name;
	return jt->second;
}

void Textures::clearTextures()
{
	textures.clear();
	tileSets.clear();
	fractionTextures.clear();
}

Data::Data()
{
	riverPlaceholder = nullptr;
	riverPlaceholderInstance = nullptr;

	loadRiverPlaceholder();
	
	loadData();
	createTypes();
}

void Data::loadData()
{
	Log::newLog("Rozpoczynam tworzenie typów - pobieranie danych");

	std::fstream data;
	std::string temp;

	data.open("info.txt", std::ios::in);

	if (!data.good()) Log::newLog("Nie uda³o siê za³adowaæ pliku info.txt");
	else
	{
		while (!data.eof())
		{
			std::getline(data, temp);

			loadSelectData(temp);
		}

		data.close();
	}
}

void Data::loadSelectData(std::string type)
{
	Log::newLog("Rozpoczynam tworzenie typów - pobieranie danych " + type);

	std::fstream fileData;
	std::string tempName, tempDirectory;

	std::map<std::string, std::string>* mapForType = new std::map<std::string, std::string>;

	fileData.open(type + "/info.txt", std::ios::in);

	if (!fileData.good()) Log::newLog("Nie uda³o siê za³adowaæ pliku " + type + "/info.txt");
	else 
	{
		while (!fileData.eof())
		{
			std::getline(fileData, tempName);
			std::getline(fileData, tempDirectory);

			mapForType->emplace(std::make_pair(tempName, tempDirectory));
		}

		datas.emplace(type, *mapForType);
		delete mapForType;
		fileData.close();
	}
}

void Data::createTypes()
{
	Log::newLog("Tworzê typy");
	std::map <std::string, std::map<std::string, std::string>>::iterator itend = datas.end();
	for (std::map <std::string, std::map<std::string, std::string>>::iterator it = datas.begin(); it != itend; it++)
	{
		std::string type = it->first;
		std::map <std::string, std::string>* singleTypeMap = &it->second;

		Log::newLog("Tworzenie typu " + type);

		std::map <std::string, std::string>::iterator jtend = singleTypeMap->end();
		for (std::map <std::string, std::string>::iterator jt = singleTypeMap->begin(); jt != jtend; jt++)
		{
			std::string typeName = jt->first;
			std::string path = jt->second;

			if (type == "biomes")
			{
				Biome* tempType = new Biome(path);
				biomes.emplace(std::make_pair(typeName, tempType));
			}
			else if (type == "buildings")
			{
				Building* tempType = new Building(path);
				buildings.emplace(std::make_pair(typeName, tempType));
			}
			else if (type == "fractions")
			{
				Fraction* tempType = new Fraction(path);
				fractions.emplace(std::make_pair(typeName, tempType));
			}
		}
	}
}


Biome* Data::getBiome(std::string type)
{
	auto it = biomes.find(type);
	if (it == biomes.end()) throw "Nie znaleziono biomu o nazwie " + type;
	return it->second;
}

Building* Data::getBuilding(std::string type)
{
	auto it = buildings.find(type);
	if (it == buildings.end()) throw "Nie znaleziono budynku o nazwie " + type;
	return it->second;
}

Fraction* Data::getFraction(std::string type)
{
	auto it = fractions.find(type);
	if (it == fractions.end()) throw "Nie znaleziono frakcji o nazwie " + type;
	return it->second;
}

void Data::loadBiomeData() ///Funkcja przestarza³a, nie u¿ywaæ!
{
	std::fstream biomeData;
	std::string tempName, tempDirectory;

	biomeData.open("biomes/info.txt", std::ios::in | std::ios::out);

	if (!biomeData.good()) std::cerr << "Nie uda³o siê za³adowaæ pliku biomes / info.txt\n";


	while (!biomeData.eof())
	{
		std::getline(biomeData, tempName);
		std::getline(biomeData, tempDirectory);

		biomeDatas.emplace(std::make_pair(tempName, tempDirectory));
	}

	biomeData.close();
}

void Data::loadRiverPlaceholder() ///Funkcja przestarza³a, nie u¿ywaæ!
{
	//riverPlaceholder = new Building("Rzeka");
	//riverPlaceholder->setCanEdit(false);

	//riverPlaceholderInstance = new BuildingInstance(riverPlaceholder);
}

void Data::addPlayer(Player* newPlayer)
{
	players.push(newPlayer);
	playersMap.emplace(std::make_pair(newPlayer->getNickName(), newPlayer));
}

Player* Data::getPlayer(std::string name)
{
	auto it = playersMap.find(name);
	if (it == playersMap.end())
	{
		std::string exception = "nie ma gracza o nicku: " + name;
		throw exception;
	}
	return it->second;
}

bool Data::checkIfPlayer(std::string name)
{
	auto it = playersMap.find(name);
	if (it == playersMap.end()) return false;
	return true;
}