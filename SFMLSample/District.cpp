#include "pch.h"
#include "District.h"

District::District(BuildingInstance* moderator)
{
	addBuilding(moderator);
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
