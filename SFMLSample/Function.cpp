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
	std::priority_queue<std::pair<float, std::pair<int, int>>> to_visit;
	const int N = 2 * ceil(amountOfMovement) + 1;
	visited->resize(2 * ceil(amountOfMovement) + 1, std::vector<float>(2 * ceil(amountOfMovement) + 1, 2 * amountOfMovement));
	to_visit.push(std::make_pair(0, std::make_pair(position.x, position.y)));
	while (!to_visit.empty())
	{
		float distance = -to_visit.top().first;
		std::pair<int, int> currentPosition = to_visit.top().second;
		to_visit.pop();
		std::pair<int, int> relativePosition(currentPosition.first - position.x, currentPosition.second - position.y);
		if (distance < (*visited)[(N + relativePosition.first) % N][(N + relativePosition.second) % N])
		{
			(*visited)[(N + relativePosition.first) % N][(N + relativePosition.second) % N] = distance;
			Tile* toCheck;
			if (currentPosition.first != 0)
			{
				toCheck = map->getTile(currentPosition.first - 1, currentPosition.second);
				if (toCheck->getType()->getCanWalkThru())
				{
					if (distance + toCheck->getType()->getMoveCost() <= amountOfMovement)
					{
						to_visit.push(std::make_pair(-(distance + toCheck->getType()->getMoveCost()), std::make_pair(currentPosition.first - 1, currentPosition.second)));
					}
				}
			}
			if (currentPosition.second != 0)
			{
				toCheck = map->getTile(currentPosition.first, currentPosition.second - 1);
				if (toCheck->getType()->getCanWalkThru())
				{
					if (distance + toCheck->getType()->getMoveCost() <= amountOfMovement)
					{
						to_visit.push(std::make_pair(-(distance + toCheck->getType()->getMoveCost()), std::make_pair(currentPosition.first, currentPosition.second - 1)));
					}
				}
			}
			if (currentPosition.first != map->getSize() - 1)
			{
				toCheck = map->getTile(currentPosition.first + 1, currentPosition.second);
				if (toCheck->getType()->getCanWalkThru())
				{
					if (distance + toCheck->getType()->getMoveCost() <= amountOfMovement)
					{
						to_visit.push(std::make_pair(-(distance + toCheck->getType()->getMoveCost()), std::make_pair(currentPosition.first + 1, currentPosition.second)));
					}
				}
			}
			if (currentPosition.second != map->getSize() - 1)
			{
				toCheck = map->getTile(currentPosition.first, currentPosition.second + 1);
				if (toCheck->getType()->getCanWalkThru())
				{
					if (distance + toCheck->getType()->getMoveCost() <= amountOfMovement)
					{
						to_visit.push(std::make_pair(-(distance + toCheck->getType()->getMoveCost()), std::make_pair(currentPosition.first, currentPosition.second + 1)));
					}
				}
			}
		}
	}
	return nullptr;
}
