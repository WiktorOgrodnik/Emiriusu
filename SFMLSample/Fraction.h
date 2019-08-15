#pragma once
#ifndef FRACTION_H
#define FRACTION_H

#include "pch.h"

class Fraction
{
private:

	std::string fractionName; ///Nazwa frakcji
	std::string fractionStyle; ///Styl u¿ywany przez frakcjê

public:

	Fraction(std::string path); 

	std::string getFractionName();
	std::string getFractionStyle();

	void setFractionName(std::string newName);
	void setFractionStyle(std::string newStyle);
};

#endif /* FRACTION_H */

