#include "pch.h"

namespace rng
{
	std::random_device rd;
	std::mt19937_64 mt(rd() + GetCurrentProcessId());
	std::uniform_real_distribution <float> urd(-1, 1);
	std::uniform_int_distribution <unsigned> uid;
	std::uniform_int_distribution <unsigned> uid2;
}

void PerlinNoise::makeHeightMap(std::vector <std::vector <float>> & map)
{
	std::vector<std::vector<float> > random_noise1(map.size(), std::vector<float>(map[0].size()));
	std::vector<std::vector<float> > random_noise2(map.size(), std::vector<float>(map[0].size()));

	gen_perlin(random_noise1);
	gen_perlin(random_noise2);

	for (unsigned i = 0; i < random_noise1.size(); i++)
	{
		for (unsigned j = 0; j < random_noise1[i].size(); j++)
		{

			float y = noise_perlin(std::make_pair(i / 128.0f, j / 128.0f), random_noise1, random_noise2) * 1.0f +
				noise_perlin(std::make_pair(i / 64.0f, j / 64.0f), random_noise1, random_noise2) * 0.5f +
				noise_perlin(std::make_pair(i / 32.0f, j / 32.0f), random_noise1, random_noise2) * 0.25f +
				noise_perlin(std::make_pair(i / 16.0f, j / 16.0f), random_noise1, random_noise2) * 0.125f;
			float out = std::min(fabs(y) * 256.0f, 256.0f);
			map[i][j] = out;
		}
	}
}

bool PerlinNoise::isThereEnoughLand(const int proc, std::vector <std::vector <int>> & map)
{
	const int required = (size_tToInt(map.size()) * size_tToInt(map[0].size()) * proc) / 100; // ile pól musi nie byc woda aby return true;
	int counter = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] != 0) counter++; // jesli cos nie jest woda to zwieksz counter
		}
	}
	//std::cerr << "Wygenerowalem mape z: " << counter << " polami" << " szukam: min. " << required << std::endl;
	if (counter >= required) return true;
	return false;
}

void PerlinNoise::GenerateMapInfo(const float ground, const float mountains, std::vector <std::vector <float>> & protoMap, std::vector <std::vector <int>> & mapInfo)
{

	std::vector < std::pair< float, std::pair<int, int> > > posort;
	for (int i = 0; i < protoMap.size(); i++)
	{
		for (int j = 0; j < protoMap[i].size(); j++)
		{
			posort.push_back(std::make_pair(protoMap[i][j], std::make_pair(i, j)));
		}
	}
	sort(posort.begin(), posort.end());

	int requiredMountains = (posort.size() * mountains);
	int requiredGround = (posort.size() * ground);
	for (int i = posort.size() - 1; i >= 0; i--)
	{
		if (requiredMountains)
		{
			mapInfo[posort[i].second.first][posort[i].second.second] = 2;
			requiredMountains--;
		}
		else if (requiredGround)
		{
			mapInfo[posort[i].second.first][posort[i].second.second] = 1;
			requiredGround--;
		}
		else
		{
			break;
		}
	}

}
void CelluralAutomata::makeBiomesMap(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <int>> & map, int a, int b, int minim, int maxim) // 0 - woda, 1 - ziemia, 2 - gory
{
	sow_seeds(mapInfo, map, a, b, minim, maxim);
	while (!filled_up(map))
	{
		for (int i = 0; i < 200; i++) expand(mapInfo, map, a, b);
		//std::cerr << "200 expandow no niezle" << std::endl;
	}
}

float CelluralAutomata::computeAverageHeight(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <float>> & protoMap, std::vector <std::vector <int>> & continents, int continent)
{
	float av = 0;
	int counter = 0;
	for (int i = 0; i < protoMap.size(); i++)
	{
		for (int j = 0; j < protoMap[i].size(); j++)
		{
			if (mapInfo[i][j] != 0 && continents[i][j] == continent)
			{
				av += protoMap[i][j];
				counter++;
			}
		}
	}
	return av / counter;
}
void CelluralAutomata::divideContinents(std::vector <std::vector <int>> & continents, std::vector <std::vector <int>> & mapInfo, int & numberOfContinents)
{
	int counter = 0;
	for (int i = 0; i < continents.size(); i++)
	{
		for (int j = 0; j < continents.size(); j++)
		{
			if (mapInfo[i][j] != 0)
			{
				if (continents[i][j] == 0)
				{
					counter++;
					std::stack <std::pair<int, int> > S;
					S.push(std::make_pair(i, j));
					while (!S.empty())
					{
						int x = S.top().first;
						int y = S.top().second;
						continents[x][y] = counter;
						S.pop();
						if (x > 0 && mapInfo[x - 1ll][y] && !continents[x - 1ll][y])
						{
							S.push(std::make_pair(x - 1, y));
						}
						if (y > 0 && mapInfo[x][y - 1ll] && !continents[x][y - 1ll])
						{
							S.push(std::make_pair(x, y - 1));
						}
						if (x < continents.size() - 1 && mapInfo[x + 1ll][y] && !continents[x + 1ll][y])
						{
							S.push(std::make_pair(x + 1, y));
						}
						if (y < continents[0].size() - 1 && mapInfo[x][y + 1ll] && !continents[x][y + 1ll])
						{
							S.push(std::make_pair(x, y + 1));
						}


					}
				}
			}
		}
	}
	numberOfContinents = counter;
}
void CelluralAutomata::makeRiversMap(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & map, std::vector <std::vector <float>> & protoMap, std::vector <std::vector <int>> & continents, int numberOfContinents, std::vector <std::vector <bool>> & protoMountains)
{
	rng::uid = std::uniform_int_distribution<unsigned>(0, map.size() - 1);
	rng::uid2 = std::uniform_int_distribution<unsigned>(0, map[0].size() - 1);
	std::vector <float> avarage(numberOfContinents + 1ll);
	for (int i = 1; i <= numberOfContinents; i++)
	{
		avarage[i] = computeAverageHeight(mapInfo, protoMap, continents, i);
		//std::cout << "AVARAGE: " << i << ": " << avarage[i] << std::endl;
	}
	//float avarage = computeAverageHeight(mapInfo, protoMap, continents, );
	int UberCounter = 0; // wszystkie pola rzek w sumie
	int z = 0;
	while (UberCounter <= 220)
	{
		z++;
		if (z == 4)z = 0;
		int x = rng::uid(rng::mt);
		int y = rng::uid2(rng::mt);
		//std::cout << "WYLOSOWALEM SB: " << protoMap[x][y] << std::endl;
		while (protoMap[x][y] < avarage[continents[x][y]] - 20.0f || mapInfo[x][y] == 0 || x < 5 || y < 5 || x > map.size() - 5 || y > map[0].size() - 5)//&& x > 0 && y > 0 && x < map.size()-1 && y < map[0].size()-1 && !map[x+1][y] && !map[x][y+1] && !map[x-1][y] && !map[x][y-1]
		{

			x = rng::uid(rng::mt);
			y = rng::uid2(rng::mt);
			//std::cout << "WYLOSOWALEM SB: " << protoMap[x][y] << std::endl;
		}
		if (x > 0 && y > 0 && map[x - 1ll][y - 1ll]) continue;
		if (x > 0 && y < map[0].size() - 1 && map[x - 1ll][y + 1ll]) continue;
		if (x < map.size() - 1 && y > 0 && map[x + 1ll][y - 1ll]) continue;
		if (x < map.size() - 1 && y < map[0].size() - 1 && map[x + 1ll][y + 1ll]) continue;
		unsigned direction = z; //rng::uid(rng::mt) % 4; // ktora cwiartka w ukladzie wspolrzednych
		unsigned direction2 = rng::uid(rng::mt) % 30 + 31; // kat nachylenia
		int counter = 0;
		std::stack< std::pair<int, int> > S;
		while (x < map.size() && y < map[0].size() && x > -1 && y > -1 && mapInfo[x][y] != 0 && map[x][y] == false)
		{
			protoMountains[x][y] = false;
			//map[x][y] = true;
			S.push(std::make_pair(x, y));
			if (x == map.size() - 1 || y == map[0].size() - 1 || x == 0 || y == 0) break;
			if (x < map.size() - 1 && map[x + 1ll][y]) break;
			if (y < map[0].size() - 1 && map[x][y + 1ll]) break;
			if (x > 0 && map[x - 1ll][y]) break;
			if (y > 0 && map[x][y - 1ll]) break;
			/*if (x > 0 && y > 0 && map[x - 1][y - 1]) break;
			if (x > 0 && y < map[0].size() - 1 && map[x - 1][y + 1]) break;
			if (x < map.size() - 1 && y > 0 && map[x + 1][y - 1]) break;
			if (x < map.size() - 1 && y < map[0].size() - 1 && map[x + 1][y + 1]) break;*/
			counter++;
			unsigned los = rng::uid(rng::mt) % 90 + 1;
			if (direction == 0)
			{
				if (los <= direction2)
				{
					x++;
				}
				else
				{
					y++;
				}
			}
			else if (direction == 1)
			{
				if (los <= direction2)
				{
					y++;
				}
				else
				{
					x--;
				}
			}
			else if (direction == 2)
			{
				if (los <= direction2)
				{
					x--;
				}
				else
				{
					y--;
				}
			}
			else if (direction == 3)
			{
				if (los <= direction2)
				{
					y--;
				}
				else
				{
					x++;
				}
			}

		}
		if (counter < 12)
		{
			//std::cout << "Znalazlem rzeke krotsza niz 12. ZOSTALA ZDEZINTEGROWANA" << std::endl;
		}
		else
		{
			UberCounter += counter;
			//std::cout << "Dobra rzeka jak chleb" << std::endl;
			while (!S.empty())
			{
				map[S.top().first][S.top().second] = true;
				S.pop();
			}
		}

	}


}
void CelluralAutomata::topologicalSkeleton(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & Mountains)
{
	std::vector <std::vector <bool>> visited;
	std::vector <std::vector <bool>> quench;
	std::vector <std::vector <int>> distance;
	visited.resize(mapInfo.size());
	distance.resize(mapInfo.size());
	quench.resize(mapInfo.size());
	for (int i = 0; i < mapInfo.size(); i++)
	{
		visited[i].resize(mapInfo[0].size());
		distance[i].resize(mapInfo[0].size());
		quench[i].resize(mapInfo[0].size());
	}

	for (int i = 0; i < Mountains.size(); i++)
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{
			int x = i;
			int y = j;
			if (x > 0 && Mountains[x][y])
			{
				distance[x][y] = distance[x - 1][y] + 1;
			}
			if (y > 0 && Mountains[x][y])
			{
				distance[x][y] = std::min(distance[x][y], distance[x][y - 1] + 1);
			}


		}
	}
	for (int i = Mountains.size() - 1; i >= 0; i--)
	{
		for (int j = Mountains[i].size() - 1; j >= 0; j--)
		{
			int x = i;
			int y = j;
			if (x < distance.size() - 1 && Mountains[x][y])
			{
				if (distance[x][y] == distance[x + 1][y] + 1) quench[x][y] = true;
				distance[x][y] = std::min(distance[x][y], distance[x + 1][y] + 1);

			}
			if (y < distance[0].size() - 1 && Mountains[x][y])
			{
				if (distance[x][y] == distance[x][y + 1] + 1 /*||  (distance[x][y] == distance[x][y + 1] && distance[x][y] == 1)*/) quench[x][y] = true;
				distance[x][y] = std::min(distance[x][y], distance[x][y + 1] + 1);
			}
		}
	}

	/*for (int i = 0; i < Mountains.size(); i++)
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{

			if (Mountains[i][j] && !visited[i][j])
			{
				std::vector < std::pair<int, int> > tiles;
				std::stack <std::pair<int, int> > S;
				S.push(std::make_pair(i, j));
				while (!S.empty())
				{
					int x = S.top().first;
					int y = S.top().second;
					visited[x][y] = true;
					tiles.push_back(std::make_pair(x, y));
					S.pop();
					if (x > 0 && mapInfo[x - 1][y] && !visited[x - 1][y] && Mountains[x - 1][y] == true)
					{
						S.push(std::make_pair(x - 1, y));
					}
					if (y > 0 && mapInfo[x][y - 1] && !visited[x][y - 1] && Mountains[x][y - 1] == true)
					{
						S.push(std::make_pair(x, y - 1));
					}
					if (x < visited.size() - 1 && mapInfo[x + 1][y] && !visited[x + 1][y] && Mountains[x + 1][y] == true)
					{
						S.push(std::make_pair(x + 1, y));
					}
					if (y < visited[0].size() - 1 && mapInfo[x][y + 1] && !visited[x][y + 1] && Mountains[x][y + 1] == true)
					{
						S.push(std::make_pair(x, y + 1));
					}
				}
				for (int k = 0; k < tiles.size(); k++)
				{
					int x = tiles[k].first;
					int y = tiles[k].second;
					int counter = 0; // z iloma wiêkszymi odemnie sasiaduje
					if (x > 0 && distance[x - 1][y] > distance[x][y]) counter++;
					if (y > 0 && distance[x][y - 1] > distance[x][y]) counter++;
					if (x < distance.size() - 1 && distance[x + 1][y] > distance[x][y]) counter++;
					if (y < distance[0].size() - 1 && distance[x][y + 1] > distance[x][y]) counter++;
					if (counter > 0) Mountains[x][y] = 0;
					rng::uid = std::uniform_int_distribution<unsigned>(1, 100);
					unsigned p = rng::uid(rng::mt);
					//if (counter == 1 && p <= 40) Mountains[x][y] = 1;

				}
			}
		}
	}*/


	/*for (int i = 0; i < Mountains.size(); i++)
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{
			if (quench[i][j]) Mountains[i][j] = 1;
			else Mountains[i][j] = 0;
		}
	}*/


	for (int i = 0; i < Mountains.size(); i++)
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{
			if (Mountains[i][j])
			{
				int x = i;
				int y = j;
				int counter = 0; // z iloma wiêkszymi odemnie sasiaduje
				if (x > 0 && distance[x - 1][y] > distance[x][y]) counter++;
				if (y > 0 && distance[x][y - 1] > distance[x][y]) counter++;
				if (x < distance.size() - 1 && distance[x + 1][y] > distance[x][y]) counter++;
				if (y < distance[0].size() - 1 && distance[x][y + 1] > distance[x][y]) counter++;
				if (counter > 0) Mountains[x][y] = 0;
				rng::uid = std::uniform_int_distribution<unsigned>(1, 100);
				unsigned p = rng::uid(rng::mt);
				if (counter == 1 && p <= 40) Mountains[x][y] = 1;
			}

		}
	}




}
void CelluralAutomata::makeMountainsMap(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & map, std::vector <std::vector <bool>> & Rivers, std::vector < std::vector <int >> & continents, int numberOfContinents)
{
	std::vector <std::vector <int> > Mountains;
	std::vector <std::vector <bool>> visited;
	Mountains.resize(mapInfo.size());
	visited.resize(mapInfo.size());
	for (int i = 0; i < Mountains.size(); i++)
	{
		Mountains[i].resize(mapInfo[i].size());
		visited[i].resize(mapInfo.size());
	}
	sow_seeds(mapInfo, Mountains, 1, 1, 10, 12);
	for (int k = 0; k < 7; k++)
	{
		for (int i = 0; i < Mountains.size(); i++)
		{
			for (int j = 0; j < Mountains[i].size(); j++)
			{
				if (Mountains[i][j])
				{

					rng::uid = std::uniform_int_distribution<unsigned>(1, 100);
					unsigned x = rng::uid(rng::mt);
					if (x <= 25 && j + 1ll < Mountains[i].size() && mapInfo[i][j + 1ll])
					{
						Mountains[i][j + 1ll] = 1;
					}
					else if (x >= 25 && x <= 50 && i + 1ll < Mountains.size() && mapInfo[i + 1ll][j])
					{
						Mountains[i + 1ll][j] = 1;
					}
					else if (x >= 50 && x <= 75 && i > 0 && mapInfo[i - 1ll][j])
					{
						Mountains[i - 1ll][j] = 1;
					}
					else if (x >= 75 && j > 0 && mapInfo[i][j - 1ll])
					{
						Mountains[i][j - 1ll] = 1;
					}


				}

			}
		}
	}
	std::vector<bool> checked_continetns(numberOfContinents + 1ll);

	for (int i = 0; i < Mountains.size(); i++) // ³atanie gór
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{
			if (mapInfo[i][j] && !Mountains[i][j] && !visited[i][j] && checked_continetns[continents[i][j]] == false)
			{
				checked_continetns[continents[i][j]] = true;
				int x = i;
				int y = j;
				visited[x][y] = true;
				std::stack < std::pair<int, int> > S;
				S.push(std::make_pair(x, y));
				while (!S.empty())
				{
					x = S.top().first;
					y = S.top().second;
					visited[x][y] = true;
					S.pop();
					if (x > 0 && mapInfo[x - 1ll][y] && !visited[x - 1ll][y] && !Mountains[x - 1ll][y])
					{
						S.push(std::make_pair(x - 1, y));
					}
					if (y > 0 && mapInfo[x][y - 1ll] && !visited[x][y - 1ll] && !Mountains[x][y - 1ll])
					{
						S.push(std::make_pair(x, y - 1));
					}
					if (x < visited.size() - 1 && mapInfo[x + 1ll][y] && !visited[x + 1ll][y] && !Mountains[x + 1ll][y])
					{
						S.push(std::make_pair(x + 1, y));
					}
					if (y < visited[0].size() - 1 && mapInfo[x][y + 1ll] && !visited[x][y + 1ll] && !Mountains[x][y + 1ll])
					{
						S.push(std::make_pair(x, y + 1));
					}
				}
			}
		}
	}
	for (int i = 0; i < Mountains.size(); i++) // ³atanie gór
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{
			if (!visited[i][j] && mapInfo[i][j] != 0 && !Rivers[i][j])
			{
				Mountains[i][j] = 1;
			}
			else
			{
				Mountains[i][j] = 0;
			}

		}
	}

	for (int i = 0; i < Mountains.size(); i++)
	{
		for (int j = 0; j < Mountains[i].size(); j++)
		{
			map[i][j] = Mountains[i][j];
		}
	}
	topologicalSkeleton(mapInfo, map);


}
int CelluralAutomata::neighbours(int b, int i, int j, std::vector <std::vector <int>> & map)
{
	int counter = 0;
	int x = map.size();
	int y = map[0].size();
	if (i != x - 1 && j != y - 1 && map[i + 1ll][j + 1ll] == b) counter++;
	if (i != 0 && j != 0 && map[i - 1ll][j - 1ll] == b) counter++;
	if (i != x - 1 && j != 0 && map[i + 1ll][j - 1ll] == b) counter++;
	if (j != y - 1 && i != 0 && map[i - 1ll][j + 1ll] == b) counter++;
	if (i != 0 && map[i - 1ll][j] == b) counter++;
	if (i != x - 1 && map[i + 1ll][j] == b) counter++;
	if (j != y - 1 && map[i][j + 1ll] == b) counter++;
	if (j != 0 && map[i][j - 1ll] == b) counter++;
	return counter;
}
bool CelluralAutomata::filled_up(std::vector <std::vector <int>> & map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (!map[i][j]) return false;
		}
	}
	return true;
}
void CelluralAutomata::expand(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <int>> & map, int a, int b)
{
	std::vector <std::vector <int> > copy(map);
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			rng::uid = std::uniform_int_distribution<unsigned>(1, 100);
			unsigned x = rng::uid(rng::mt);
			if ((mapInfo[i][j] == 1 && x <= 45) || (x <= 15))
			{
				int connections = 0;

				if (map[i][j] != 0)
				{
					connections = neighbours(map[i][j], i, j, map);
				}
				for (int k = a; k <= b; k++)
				{

					if (connections <= 4 && neighbours(k, i, j, map) > connections)
					{
						copy[i][j] = k;
						break;
					}
				}
				//std::cout << copy[i][j] << std::endl;
			}
		}
	}
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			map[i][j] = copy[i][j];
		}
	}
}
void CelluralAutomata::sow_seeds(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <int>> & map, int a, int b, int minim, int maxim)
{
	std::vector< std::pair<int, int> > list;

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (mapInfo[i][j] != 0)
			{
				list.push_back(std::make_pair(i, j));
			}
		}
	}
	if (!list.empty())
	{
		//list.push_back(std::make_pair(0, 0));
		std::vector<int> B(b + 1ll); //ilosc ziaren dla poszczegolnych biomow

		rng::uid = std::uniform_int_distribution<unsigned>(minim, maxim);

		for (int i = a; i <= b; i++)
		{
			B[i] = rng::uid(rng::mt);
		}

		int i = a;
		while (i <= b)
		{
			rng::uid = std::uniform_int_distribution<unsigned>(0, list.size() - 1);

			int z = rng::uid(rng::mt);
			/*	int o = 0;
				int limit = (list.size() - 1)/( minim / 5 + 1);
				rng::uid = std::uniform_int_distribution<unsigned>(0, limit);
				int z = rng::uid(rng::mt);
				o += z + limit;
				if (o >= list.size() - 1) o -= list.size() - 1;*/

			int x = list[z].first;
			int y = list[z].second;

			//if (mapInfo[x][y] == 1 /* && map[x][y] == 0*/) // to sie odkomentuje jak perlin bedzie w stanie stworzyc mape z przynajmniej 12 ladami
			{

				map[x][y] = i;
				B[i]--;
			}
			//std::cerr << "Sieje ziarno biomu " << i << " na: " << x << " " << y << std::endl;
			if (B[i] == 0)
			{
				i++;
			}
		}
	}
	else
	{
		map[0][0] = a;
	}
}


void PerlinNoise::gen_perlin(std::vector<std::vector<float> > &V)
{
	for (unsigned i = 0; i < V.size(); i++)
	{
		for (unsigned j = 0; j < V[i].size(); j++)
		{
			V[i][j] = rng::urd(rng::mt);
		}
	}
}

float PerlinNoise::dot_perlin(const std::pair<float, float> &A, const std::pair<float, float> &B)
{
	return A.first * A.second + B.first * B.second;
}

float PerlinNoise::fade_perlin(float t)
{
	return t * t*t*(t*(t*6.0f - 15.0f) + 10.0f);
}

float PerlinNoise::grad_perlin(float p, std::vector<std::vector<float> > &V)
{
	float v = V[0][(int)round(p) % V[0].size()];
	return v > 0.5f ? 1.0f : -1.0f;
}

std::pair<float, float> PerlinNoise::grad_perlin(std::pair<float, float> p, std::vector<std::vector<float> > &V1, std::vector<std::vector<float> > &V2)
{
	std::pair<float, float> v;
	unsigned index_X1 = std::min(abs((int)round(p.first)), (int)V1.size());
	unsigned index_Y1 = std::min(abs((int)round(p.second)), (int)V1.size());
	unsigned index_X2 = std::min(abs((int)round(p.first)), (int)V1.size());
	unsigned index_Y2 = std::min(abs((int)round(p.second)), (int)V1.size());
	v.first = V1[index_X1][index_Y2];
	v.second = V2[index_X2][index_Y2];
	return v;
}

float PerlinNoise::noise_perlin(std::pair<float, float> p, std::vector<std::vector<float> > &V1, std::vector<std::vector<float> > &V2)
{
	std::pair<float, float> p0 = std::make_pair(floor(p.first), floor(p.second));
	std::pair<float, float> p1 = std::make_pair(p0.first + 1, p0.second);
	std::pair<float, float> p2 = std::make_pair(p0.first, p0.second + 1);
	std::pair<float, float> p3 = std::make_pair(p0.first + 1, p0.second + 1);

	std::pair<float, float> g0 = grad_perlin(p0, V1, V2);
	std::pair<float, float> g1 = grad_perlin(p1, V1, V2);
	std::pair<float, float> g2 = grad_perlin(p2, V1, V2);
	std::pair<float, float> g3 = grad_perlin(p3, V1, V2);

	float t0 = p.first - p0.first;
	float fade_t0 = fade_perlin(t0);

	float t1 = p.second - p0.second;
	float fade_t1 = fade_perlin(t1);

	std::pair <float, float> X1 = std::make_pair(p.first - p0.first, p.second - p0.second);
	std::pair <float, float> X2 = std::make_pair(p.first - p1.first, p.second - p1.second);
	std::pair <float, float> X3 = std::make_pair(p.first - p2.first, p.second - p2.second);
	std::pair <float, float> X4 = std::make_pair(p.first - p3.first, p.second - p3.second);

	float p0p1 = (1.0f - fade_t0) * dot_perlin(g0, X1) + fade_t0 * dot_perlin(g1, X2);
	float p2p3 = (1.0f - fade_t0) * dot_perlin(g2, X3) + fade_t0 * dot_perlin(g3, X4);

	return (1.0f - fade_t1) * p0p1 + fade_t1 * p2p3;

}

float PerlinNoise::noise_perlin(float p, std::vector<std::vector<float> > &V)
{
	float p0 = floor(p);
	float p1 = p0 + 1.0f;

	float t = p - p0;
	float fade_t = fade_perlin(t);

	float g0 = grad_perlin(p0, V);
	float g1 = grad_perlin(p1, V);

	return (1.0f - fade_t)*g0*(p - p0) + fade_t * g1*(p - p1);
}

void Random::generateStartingPositions(int numberOfPlayers, std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & Mountains, std::vector <std::vector <bool>> & Rivers, std::vector <std::vector <int>> & Players)
{
	std::vector< std::pair<int, int> > list;

	for (int i = 0; i < mapInfo.size(); i++)
	{
		for (int j = 0; j < mapInfo[i].size(); j++)
		{
			if (mapInfo[i][j] != 0 && !Mountains[i][j] && !Rivers[i][j])
			{
				list.push_back(std::make_pair(i, j));
			}
		}
	}
	for (int i = 1; i <= numberOfPlayers; i++)
	{
		rng::uid = std::uniform_int_distribution<unsigned>(0, list.size() - 1);
		int z = rng::uid(rng::mt);
		if (!Players[list[z].first][list[z].second]) Players[list[z].first][list[z].second] = i;
		else
		{
			i--;
			continue;
		}
	}


}

/* bool QTN::quadLeaf()
{
	if (first->getValue() == second->getValue() && first->getValue() == third->getValue() && first->getValue() == fourth->getValue() && first->getValue() != -1)
	{
		return true;
	}
	else return false;
}

QTN::QTN(const std::vector <std::vector <int>> & map, const std::pair <int, int> & top, const std::pair <int, int> bottom, int l)
{
	lvl = l;
	v = -1;

	if (lvl == 1)
	{
		first = nullptr;
		second = nullptr;
		third = nullptr;
		fourth = nullptr;

		v = map[top.first][top.second];
	}
	else
	{
		first = new QTN(map, top, std::make_pair(bottom.first / 2, bottom.second / 2), l - 1);
		second = new QTN(map, std::make_pair(bottom.second / 2 + 1, top.second), std::make_pair(bottom.first / 2, bottom.second), l - 1);
		third = new QTN(map, std::make_pair(bottom.first / 2 + 1, top.second), std::make_pair(bottom.first, bottom.second / 2), l - 1);
		fourth = new QTN(map, std::make_pair(bottom.first / 2 + 1, bottom.second / 2 + 1), bottom, l - 1);

		if (quadLeaf())
		{
			v = first->getValue();

			delete first; first = nullptr;
			delete second; second = nullptr;
			delete third; third = nullptr;
			delete fourth; fourth = nullptr;
		}
	}
}

QTN::~QTN()
{
	delete first;
	delete second;
	delete third;
	delete fourth;
}

QuadTree::QuadTree(const int & n, const std::vector <std::vector <int>> & map, int lvl)
{
	root = new QTN(map, std::make_pair(0, 0), std::make_pair(n - 1, n - 1), lvl);
}*/


