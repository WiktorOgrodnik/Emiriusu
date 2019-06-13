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

Building::Building(std::string name_)
{
	canEdit = true;
	name = name_;
}

void Building::setCanEdit(bool canEdit_)
{
	canEdit = canEdit_;
}

BuildingInstance::BuildingInstance(Building* newBuilding)
{
	type = newBuilding;
}

void BuildingInstance::setType(Building* newType)
{
	type = newType;
}
