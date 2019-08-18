#pragma once
#ifndef FRACTION_H
#define FRACTION_H

#include "pch.h"

class Fraction
{
private:

	std::string fractionName; ///Nazwa frakcji
	std::string fractionStyle; ///Styl u¿ywany przez frakcjê

	///Zablokowanie mo¿liwoœci kopiowania
	Fraction operator= (const Fraction& other) {}
	Fraction(const Fraction& other) {}

public:

	Fraction(std::string path); ///Konstruktor - przyjmuje nazwê pliku frakcji, z którego pobiera dane

	/// Gettery
	std::string getFractionName();
	std::string getFractionStyle();

	/// Settery
	void setFractionName(std::string newName);
	void setFractionStyle(std::string newStyle);
};

#endif /* FRACTION_H */

