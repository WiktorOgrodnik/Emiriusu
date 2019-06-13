#pragma once
#ifndef GENERATOR_H
#define GENERATOR_H

#include "pch.h"

namespace rng ///zmienne u¿ywane do losowania 
{
	extern std::random_device rd;
	extern std::mt19937_64 mt;
	extern std::uniform_real_distribution <float> urd;
	extern std::uniform_int_distribution <unsigned> uid;
	extern std::uniform_int_distribution <unsigned> uid2;
}


class PerlinNoise
{
	/// funkcje wykorzystywane przez Perlin Noise
	static void gen_perlin(std::vector<std::vector<float> > &V);
	static float dot_perlin(const std::pair<float, float> &A, const std::pair<float, float> &B);
	static float fade_perlin(float t);
	static float grad_perlin(float p, std::vector<std::vector<float> > &V);
	static std::pair<float, float> grad_perlin(std::pair<float, float> p, std::vector<std::vector<float> > &V1, std::vector<std::vector<float> > &V2);
	static float noise_perlin(std::pair<float, float> p, std::vector<std::vector<float> > &V1, std::vector<std::vector<float> > &V2);
	static float noise_perlin(float p, std::vector<std::vector<float> > &V);

public:
	static void GenerateMapInfo(const float ground, const float mountains, std::vector <std::vector <float>> & protoMap, std::vector <std::vector <int>> & mapInfo);/// przyjmuje procent l¹du, gór, HeightMap i mapInfo ktore modyfikuje
	static bool isThereEnoughLand(const int proc, std::vector <std::vector <int>> & map);
	static void makeHeightMap(std::vector <std::vector <float>> & map); /// wywo³anie szumu perlina (przyjmuje:  pusty wektor wektor intów na dane)
};

class CelluralAutomata
{
	static void sow_seeds(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <int>> & map, int a, int b, int minim, int maxim);
	static void expand(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <int>> & map, int a, int b);
	static int neighbours(int b, int i, int j, std::vector <std::vector <int>> & map);
	static bool filled_up(std::vector <std::vector <int>> & map);
	static float computeAverageHeight(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <float>> & protoMap, std::vector <std::vector <int>> & continents, int continent);

public:
	static void makeBiomesMap(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <int>> & map, int a, int b, int minim, int maxim); ///  (przyjmuje : mape z informacjami z perlina(woda,gory,ziemia) , pusta mape (obie juz zresizowane), przedzia³ liczb dla których ma wygenerowaæ te biomy (np. 3-5)) minimalna liczbe i maksymalna liczbe tych biomów
	static void makeRiversMap(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & map, std::vector <std::vector <float>> & protoMap, std::vector <std::vector <int>> & continents, int numberOfContinents, std::vector <std::vector <bool>> & protoMounatins); /// (przyjmuje : mape z informacjami z perlina(woda,gory,ziemia) , pusta mape (obie juz zresizowane), w miejscach z rzekami ustawia wartosc pustej mapy na true;
	static void makeMountainsMap(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & map, std::vector <std::vector <bool>> & Rivers, std::vector < std::vector <int >> & continents, int numberOfContinents); // tworzy pasma górskie w losowych miejscach
	static void divideContinents(std::vector <std::vector <int>> & continents, std::vector <std::vector <int>> & mapInfo, int & numberOfContinents); // kazdemu kontynentowi przypisuje unikalna liczbe, wyznacza numberofContinates
	static void topologicalSkeleton(std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & Mountains); // robi topological skeleton z gór przyjmuje mapInfo i tablice booli gdzie s¹ góry
};
class Random
{
	public:
	static void generateStartingPositions(int numberOfPlayers, std::vector <std::vector <int>> & mapInfo, std::vector <std::vector <bool>> & Mountains, std::vector <std::vector <bool>> & Rivers, std::vector <std::vector <int>> & Players);
};

class QTN
{
	int lvl;
	int v;
	QTN* first;
	QTN* second;
	QTN* third;
	QTN* fourth;

	bool quadLeaf();

public:

	QTN(const std::vector <std::vector <int>> & map, const std::pair <int, int> & top, const std::pair <int, int> bottom, int l);
	int getValue() { return v; }
	~QTN();
};

class QuadTree
{
	QTN* root;

public:

	QuadTree(const int & n, const std::vector <std::vector <int>> & map, int lvl);
};

#endif /* GENERATOR_H */

