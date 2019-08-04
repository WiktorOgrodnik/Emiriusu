#include "pch.h"

Biome::Biome(std::string fileName)
{
	std::fstream biomeData;
	std::string tempText;
	biomeData.open(fileName, std::ios::in | std::ios::out);

	if (!biomeData.good()) std::cerr << "Nie uda³o siê za³adowaæ pliku " << fileName << '\n';


	std::getline(biomeData, tempText);
	id = stringToInt(tempText);
	std::getline(biomeData, tempText);
	name = tempText;
	std::getline(biomeData, tempText);
	moveCost = stringToFloat(tempText);
	std::getline(biomeData, tempText);
	opacity = stringToFloat(tempText);
	std::getline(biomeData, tempText);
	food = stringToShort(tempText);
	std::getline(biomeData, tempText);
	stone = stringToShort(tempText);
	std::getline(biomeData, tempText);
	wood = stringToShort(tempText);
	std::getline(biomeData, tempText);
	canBuildACity = stringToBool(tempText);
	std::getline(biomeData, tempText);
	canWalkThru = stringToBool(tempText);
	std::getline(biomeData, tempText);
	specialStuff = tempText;

	biomeData.close();
}

Building::Building(std::string fileName)
{
	std::fstream buildingData;
	std::string tempText;
	buildingData.open(fileName, std::ios::in);

	if (!buildingData.good()) Log::newLog("Nie uda³o siê za³adowaæ pliku " + fileName);
	else
	{
		std::getline(buildingData, tempText);
		name = tempText;
		std::getline(buildingData, tempText);
		texture = tempText;
		std::getline(buildingData, tempText);
		canEdit = stringToBool(tempText);
		
		buildingData.close();
	}
}

void Building::setCanEdit(bool canEdit_)
{
	canEdit = canEdit_;
}

BuildingInstance::BuildingInstance(Building* newBuilding, sf::Vector2f newPos, std::pair<unsigned, unsigned> additionalPos)
{
	type = newBuilding;
	position.x = newPos.x;
	position.y = newPos.y;

	Log::newLog("Tworzê budynek na pozycji (w pikselach): " + std::to_string(float(newPos.x) * tileResolution + additionalPos.first) + " " + std::to_string(float(newPos.y) * tileResolution + additionalPos.second));

	texture = Engine::getInstance().getData().Textures().getTexture(newBuilding->getTextureId());
	body.setTexture(texture);
	body.setSize(sf::Vector2f(miniTileResolution, miniTileResolution));
	body.setPosition(float(newPos.x) * tileResolution + additionalPos.first, float(newPos.y) * tileResolution + additionalPos.second);

	Engine::getInstance().addToRenderObjects(this, 2);
}

void BuildingInstance::setType(Building* newType)
{
	type = newType;
}

void BuildingInstance::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void BuildingInstance::draw(sf::RenderWindow& window, sf::View& view, float zoom)
{
	window.draw(body);
}

void BuildingInstance::draw(sf::RenderTexture& texture)
{
	texture.draw(body);
}
