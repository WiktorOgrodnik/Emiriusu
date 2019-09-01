#include "pch.h"

Biome::Biome(std::string fileName)
{
	std::fstream biomeData;
	std::string tempText;
	biomeData.open(fileName, std::ios::in | std::ios::out);

	if (!biomeData.good())
	{
		Log::newLog("Nie uda³o siê za³adowaæ pliku " + fileName);
		id = 0;
		name = "";
		moveCost = 0.0;
		opacity = 0.0;
		food = 0;
		stone = 0;
		wood = 0;
		canBuildACity = false;
		canWalkThru = false;
		specialStuff = "";
	}
	else
	{
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
}

std::string Biome::getName()
{
	return name;
}

int Biome::getId() 
{ 
	return id; 
}

float Biome::getMoveCost() 
{ 
	return moveCost; 
}

short Biome::getFood() 
{ 
	return food; 
}

short Biome::getStone() 
{ 
	return stone; 
}

short Biome::getWood() 
{ 
	return wood; 
}

bool Biome::getCanBuildACity() 
{ 
	return canBuildACity; 
}

bool Biome::getCanWalkThru()
{ 
	return canWalkThru; 
}

std::string Biome::getSpecialStuff() 
{ 
	return specialStuff; 
}

sf::Color* Biome::getBiomeColor() 
{ 
	return &biomeColor; 
}

void Biome::setColor(char r, char g, char b, char transparency)
{
	biomeColor.r = r; biomeColor.g = g; biomeColor.b = b;
}

Building::Building(std::string fileName)
{
	std::fstream buildingData;
	std::string tempText;
	buildingData.open(fileName, std::ios::in);

	if (!buildingData.good())
	{
		Log::newLog("Nie uda³o siê za³adowaæ pliku " + fileName);

		name = "";
		texture = "default";
		canEdit = false;
		districtType = "";
	}
	else
	{
		std::getline(buildingData, tempText);
		name = tempText;
		std::getline(buildingData, tempText);
		texture = tempText;
		std::getline(buildingData, tempText);
		canEdit = stringToBool(tempText);
		std::getline(buildingData, tempText);
		districtType = tempText;
		
		buildingData.close();
	}
}

void Building::setCanEdit(bool canEdit_)
{
	canEdit = canEdit_;
}

void Building::setDistrictType(std::string newDistrictType)
{
	districtType = newDistrictType;
}

std::string Building::getName() 
{ 
	return name; 
}

std::string Building::getTextureId() 
{
	return texture; 
}

bool Building::getCanEdit() 
{ 
	return canEdit; 
}

std::string Building::getDistrictType()
{
	return districtType;
}

BuildingInstance::BuildingInstance(Building* newBuilding, sf::Vector2f newPos, std::pair<unsigned, unsigned> additionalPos, Player* player, std::pair <short, short> newCityPos)
{
	type = newBuilding;
	cityPos = newCityPos;
	position.x = newPos.x;
	position.y = newPos.y;

	Log::newLog("Tworzê budynek na pozycji (w pikselach): " + std::to_string(float(newPos.x) * tileResolution + additionalPos.first) + " " + std::to_string(float(newPos.y) * tileResolution + additionalPos.second) + " dla gracza: " + player->getNickName());

	texture = Engine::getInstance().getData().Textures().getFractionTexture(player->getFraction(), newBuilding->getTextureId());
	body.setTexture(texture);
	body.setSize(sf::Vector2f(miniTileResolution, miniTileResolution));
	body.setPosition(float(newPos.x) * tileResolution + additionalPos.first, float(newPos.y) * tileResolution + additionalPos.second);

	owner = player;
	locke = false;

	Engine::getInstance().addToRenderObjects(this, 2);
}

void BuildingInstance::setType(Building* newType)
{
	type = newType;
}

Building* BuildingInstance::getType()
{
	return type;
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

void BuildingInstance::setOwner(Player* newPlayer)
{
	owner = newPlayer;
}

Player* BuildingInstance::getOwner()
{
	return owner;
}

void BuildingInstance::addToDistrict()
{
	Engine::getInstance().getData().addDistrict(this);
}

std::vector <BuildingInstance*> BuildingInstance::getFriends()
{
	try
	{
		return Engine::getInstance().getData().getCity(this)->getFriends(cityPos);
	}
	catch (std::string exception) { Log::newLog("Napotkano wyj¹tek (funkcja getFriends): " + exception); }
}

BuildingInstance::~BuildingInstance()
{
	lock();

	Engine::getInstance().getData().reportDestructionBuildingInstance(this);

	Engine::getInstance().deleteFormRenderObjects(this);

	Engine::getInstance().getData().refreshDistricts(owner);
}

void BuildingInstance::lock()
{
	Log::newLog("Zablokowano budynek");
	locke = true;
}

void BuildingInstance::unlock()
{
	Log::newLog("Odblokowano budynek");
	locke = false;
}

bool BuildingInstance::getLock()
{
	return locke;
}
