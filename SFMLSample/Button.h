#pragma once
#include "pch.h" 
#include "Selectable.h"
class Button : public Selectable
{
	Function* activationFunction;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	sf::Color idlecolor;
	sf::Color activecolor;

public:
	Button(float x, float y, float width, float height, sf::RectangleShape shape, sf::Font font, sf::Text text, sf::Color idlecolor, sf::Color activecolor);
	~Button();
	void setActivationFunction(Function* newActivationFunction) { activationFunction = newActivationFunction; }
	Function* getActivationFunction() { return activationFunction; }
	virtual Function* onSelect()override;
	virtual Function* onClick()override;
	virtual Function* onDeselect()override;
};