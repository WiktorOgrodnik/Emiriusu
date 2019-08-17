#pragma once
#ifndef DISTRICT_H
#define DISTRICT_H

#include "pch.h"

class District
{
private:

	std::set <BuildingInstance*> buildings;

public:

	District(BuildingInstance* moderator);

	void addBuilding(BuildingInstance* newBuilding);
	void deleteBuilding(BuildingInstance* building);
	std::set <BuildingInstance*> exportData();

	int getNumberOfBuildings();

};

#endif /* DISTRICT_H */

