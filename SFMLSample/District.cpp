#include "pch.h"
#include "District.h"

District::District(BuildingInstance* moderator)
{
	addBuilding(moderator);
	setOwner(moderator->getOwner());
}

void District::setOwner(Player* newOwner)
{
	owner = newOwner;
}

std::set <BuildingInstance*> District::exportData()
{
	std::set <BuildingInstance*> exit = buildings;
	buildings.clear();
	return exit;
}

void District::addBuilding(BuildingInstance* newBuilding)
{
	buildings.emplace(newBuilding);
}

int District::getNumberOfBuildings()
{
	return buildings.size();
}

Player* District::getOwner()
{
	return owner;
}
