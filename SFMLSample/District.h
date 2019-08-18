#pragma once
#ifndef DISTRICT_H
#define DISTRICT_H

#include "pch.h"

class District
{
private:

	std::set <BuildingInstance*> buildings; /// Budynki nale¿¹ce do dzielnicy

	Player* owner; /// W³aœciciel dzielnicy
	void setOwner(Player* newOwner); /// Ustawa w³aœcicela dzielnicy

	///Zablokowanie mo¿liwoœci kopiowania
	District operator= (const District& other) {}
	District(const District& other) {}

public:

	District(BuildingInstance* moderator); /// Konstruktor - przyjmuje moderatora (budynek tworzacy dzielnicê, puste dzielnice s¹ usuwane)

	void addBuilding(BuildingInstance* newBuilding); /// Dodaje nowy budynek do dzielnicy
	std::set <BuildingInstance*> exportData(); /// Eksportuje dane w celu usuniêcia dzielnicy

	int getNumberOfBuildings(); /// Zwraca liczbê budynków w dzielnicy
	Player* getOwner(); /// Zwraca w³aœciciela

};

#endif /* DISTRICT_H */

