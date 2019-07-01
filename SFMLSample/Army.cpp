#include "pch.h"

Army::Army(sf::Vector2i newPosition, Map& map, sf::Texture* newTexture)
{
	position = newPosition;
	map.getTile(newPosition.x, newPosition.y)->setArmy(this);

	texture = newTexture;
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
	body.setPosition(float(position.x) * tileResolution, float(position.y) * tileResolution);

	armyType = 0;
	armyExtra = 0;
	amountOfMovement = 10;
	unitCount = 0;

	onSelectFunction = new Dijkstra; /// powinno zostaæ zast¹piona globalnym wskaŸnikiem
}

Army::~Army()
{
}

void Army::draw(sf::RenderWindow & window)
{
	window.draw(body);
}

void Army::draw(sf::RenderWindow & window, sf::View & view, float zoom)
{
	window.draw(body);
}

void Army::draw(sf::RenderTexture & texture)
{
	texture.draw(body);
}

void Army::addUnit(Unit * newUnit)
{
	units.push_back(newUnit);
}

void Army::mergeArmies(Army * secondArmy)
{
	for (unsigned i = 0; i < secondArmy->getNumberOfUnits(); i++)
	{
		units.push_back(secondArmy->getUnit(i));
	}
}

unsigned Army::getNumberOfUnits()
{
	return unitCount;
}

bool Army::move(sf::Vector2i targetPosition, Map & map)
{
	std::priority_queue<std::pair<float, std::pair<int, int>>> to_visit;
	std::vector<std::vector<bool> > visited(2.0f * ceil(amountOfMovement) + 1.0f, std::vector<bool>(2ll * ceil(amountOfMovement) + 1ll));
	const int N = 2 * ceil(amountOfMovement) + 1;
	to_visit.push(std::make_pair(0, std::make_pair(position.x, position.y)));
	while (!to_visit.empty())
	{
		float odl = -to_visit.top().first;
		std::pair<int, int> index = to_visit.top().second;
		to_visit.pop();
		//std::cout << index.first - position.x << " " << index.second - position.y << "\n";
		//std::cout << odl << std::endl;
		if (targetPosition.x == index.first && targetPosition.y == index.second)
		{
			//std::cerr << "Target pos: (" << targetPosition.x << ", " << targetPosition.y << ")\nIndex: (" << index.first << ", " << index.second << ")\n";

			//position = targetPosition;
			return true;
		}
		else
		{
			//std::cerr << "Target pos: (" << targetPosition.x << ", " << targetPosition.y << ")\nIndex: (" << index.first << ", " << index.second << ")\n";

		}

		if (visited[(N + (index.first - position.x)) % N][(N + (index.second - position.y)) % N] == 1)
			continue;
		visited[(N + (index.first - position.x)) % N][(N + (index.second - position.y)) % N] = 1;
		Tile *to_check = nullptr;
		if (index.first != 0)
		{
			to_check = map.getTile(index.first - 1, index.second);
			if (to_check->getType()->getCanWalkThru())
			{
				if (odl + to_check->getType()->getMoveCost() <= amountOfMovement)
				{
					to_visit.push(std::make_pair(-(odl + to_check->getType()->getMoveCost()), std::make_pair(index.first - 1, index.second)));
				}
			}
		}
		if (index.second != 0)
		{

			to_check = map.getTile(index.first, index.second - 1);
			if (to_check->getType()->getCanWalkThru())
			{
				if (odl + to_check->getType()->getMoveCost() <= amountOfMovement)
				{
					to_visit.push(std::make_pair(-(odl + to_check->getType()->getMoveCost()), std::make_pair(index.first, index.second - 1)));
				}
			}
		}
		if (index.first != map.getSize() - 1)
		{

			to_check = map.getTile(index.first + 1, index.second);
			//std::cout << to_check->getType()->getCanWalkThru() << " " << to_check->getType()->getMoveCost() << std::endl;
			if (to_check->getType()->getCanWalkThru())
			{
				if (odl + to_check->getType()->getMoveCost() <= amountOfMovement)
				{
					to_visit.push(std::make_pair(-(odl + to_check->getType()->getMoveCost()), std::make_pair(index.first + 1, index.second)));
				}
			}
		}
		if (index.second != map.getSize() - 1)
		{
			to_check = map.getTile(index.first, index.second + 1);
			if (to_check->getType()->getCanWalkThru())
			{
				if (odl + to_check->getType()->getMoveCost() <= amountOfMovement)
				{
					to_visit.push(std::make_pair(-(odl + to_check->getType()->getMoveCost()), std::make_pair(index.first, index.second + 1)));
				}
			}
		}
	}
	return false;

}

Unit * Army::getUnit(unsigned index)
{
	return units[index];
}

void Army::setPosition(sf::Vector2i newPosition)
{
	position = newPosition;
	body.setPosition(sf::Vector2f(newPosition.x * tileResolution, newPosition.y * tileResolution));
}

void Army::setArmyType(char newArmyType)
{
	armyType = newArmyType;
}

Function* Army::onSelect()
{
	std::vector<void*> data;
	data.push_back((void*) &position);
	data.push_back((void*) &amountOfMovement);
	data.push_back((void*) &movesData);
	data.push_back((void*) Engine::getInstance().mapPointer);
	onSelectFunction->Activate(data); /// pozycja armi(sf::Vector2i), iloœæ ruchu armii(float), tablica do danych(vector<vector<float>>), mapa(Map*)
	return onSelectFunction;
}

Function* Army::onClick()
{
	/// do stuff
	this->onSelect();
	return nullptr;
}

Function* Army::onDeselect()
{
	movesData.clear();
	return nullptr;
}

void Army::setTexture(sf::Texture* newTexture)
{
	body.setTexture(newTexture);
	body.setSize(sf::Vector2f(tileResolution, tileResolution));
}

