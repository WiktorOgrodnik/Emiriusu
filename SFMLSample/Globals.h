#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include "pch.h"

extern const char tileResolution = 96;
extern const char miniTileResolution = 32;

unsigned convertXAndYToIndex(const unsigned x, const unsigned y); /// konwertuje X i Y na index (dla miniTile) (funkcja nieu¿ywana)

template<typename T1, typename T2> /// template
constexpr auto MOD(T1 a, T2  b) { return (a < 0 ? (((a % b) + b) % b) : (a % b)); } /// matematyczne modulo (przyjmuje dwie dowolne liczby)

int stringToInt(const std::string a); /// zamienia string na int
bool stringToBool(const std::string s); /// zamienia string na bool
float stringToFloat(const std::string a); /// zamienia string na float
short stringToShort(const std::string s); /// zamienia string na short
int size_tToInt(size_t a); /// zamienia size_t

enum Types
{
	ITEGER,
	FLOATVAL,
	VOIDPOINTER
};  // tutaj id¹ wykorzytwane przez klasy Function typy danych np. INT, FLOAT itd.


#endif /* GLOBALS_H */