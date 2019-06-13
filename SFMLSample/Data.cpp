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
}

void Textures::loadOtherTextures()
{
	std::fstream textureInfoFile;
	const std::string textureInfoFileName = "textures/other.txt";
	std::string tempText, tempText2;

	textureInfoFile.open(textureInfoFileName, std::ios::in | std::ios::out);
	if (!textureInfoFile.good()) std::cerr << "Nie uda�o si� odczyta� pliku: " << textureInfoFileName << '\n';

	while (!textureInfoFile.eof())
	{
		std::getline(textureInfoFile, tempText);
		std::getline(textureInfoFile, tempText2);

		sf::Texture* tempTexture = new sf::Texture;
		tempTexture->loadFromFile(tempText2);
		textures.insert(std::make_pair(tempText, tempTexture));
	}
}

void Textures::loadTileSets()
{
	std::fstream textureInfoFile;
	const std::string textureInfoFileName = "textureInfo.txt";
	std::string tempText, tempText2;
	std::queue <std::string> fileQueue;

	textureInfoFile.open(textureInfoFileName, std::ios::in | std::ios::out);

	if (!textureInfoFile.good()) std::cerr << "Nie uda�o si� odczyta� pliku: " << textureInfoFileName << '\n';

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

		textureInfoFile.open(tempText2, std::ios::in | std::ios::out);

		if (!textureInfoFile.good()) std::cerr << "Nie uda�o si� za�adowa� pliku " << tempText2 << '\n';

		sf::Texture* tileSet = it->second;

		std::getline(textureInfoFile, tempText);
		x = stringToInt(tempText);
		std::getline(textureInfoFile, tempText);
		y = stringToInt(tempText);

		tileSet->create(x * tileResolution, y * tileResolution);

		for(int i = 0; i < x * y + 1; i++)
		{
			std::getline(textureInfoFile, tempText);

			if (tempText == "variants")
			{
				varaints = true;
				numberOfTextures = 0;
			}

			if (!varaints)
			{
				if (!tempTexture.loadFromFile(tempText)) std::cerr << "Nie uda�o si� za�adowa� tekstury " << tempText << '\n';

				tileSet->update(tempTexture, tileResolution * numberOfTextures, 0);

				numberOfTextures++;
			}
			else if (tempText != "variants")
			{
				if (!tempTexture.loadFromFile(tempText))std::cerr << "Nie uda�o si� za�adowa� tekstury " << tempText << '\n';
			
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

sf::Texture* Textures::getTileSet(std::string name)
{
	std::map <std::string, sf::Texture*>::iterator it = tileSets.find(name);
	return it->second;
}

sf::Texture* Textures::getTexture(std::string name)
{
	std::map <std::string, sf::Texture*>::iterator it = textures.find(name);
	return it->second;
}

void Textures::clearTextures()
{
	textures.clear();
	tileSets.clear();
}

Data::Data()
{
	riverPlaceholder = nullptr;
	riverPlaceholderInstance = nullptr;
	loadRiverPlaceholder();
	loadBiomeData();
	std::map <std::string, std::string>::iterator itend = biomeDatas.end();
	for (std::map <std::string, std::string>::iterator it = biomeDatas.begin(); it != itend; it++)
	{
		Biome* tempBiome = new Biome(it->second);

		biomes.emplace(std::make_pair(it->first, tempBiome));
	}
}

void Data::loadBiomeData()
{
	std::fstream biomeData;
	std::string tempName, tempDirectory;

	biomeData.open("biomes/info.txt", std::ios::in | std::ios::out);

	if (!biomeData.good()) std::cerr << "Nie uda�o si� za�adowa� pliku biomes / info.txt\n";


	while (!biomeData.eof())
	{
		std::getline(biomeData, tempName);
		std::getline(biomeData, tempDirectory);

		biomeDatas.emplace(std::make_pair(tempName, tempDirectory));
	}

	biomeData.close();
}

Biome* Data::getBiome(std::string biome)
{
	auto it = biomes.find(biome);
	return it->second;
}

void Data::loadRiverPlaceholder()
{
	riverPlaceholder = new Building("Rzeka");
	riverPlaceholder->setCanEdit(false);

	riverPlaceholderInstance = new BuildingInstance(riverPlaceholder);
}