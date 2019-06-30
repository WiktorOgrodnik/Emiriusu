#include "pch.h"
#include "Function.h"


Function::Function()
{
}


Function::~Function()
{
}

void* Dijkstra::Activate(std::vector<void*> data) /// pozycja armi(sf::Vector2i), iloœæ ruchu armii(float), tablica do danych(vector<vector<float>>), mapa(Map*)
{
	sf::Vector2i position = *((sf::Vector2i*)data[0]);
	float amountOfMovement = *((float*)data[1]);
	std::vector<std::vector<float>>* visited = (std::vector<std::vector<float>>*)data[2];
	Map* map = (Map*)data[3];
	return nullptr;
}
