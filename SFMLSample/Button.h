#pragma once
#include "pch.h" 
#include "Selectable.h"
class Button : public InterfaceSelectable, public Interface
{
	Function* activationFunction;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	sf::Color idlecolor;
	sf::Color activecolor;
	sf::Color hovercolor;

public:
	Button(float x, float y, float width, float height, sf::RectangleShape shape, sf::Font font, sf::Text text, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor);
	~Button();
	void setActivationFunction(Function* newActivationFunction) { activationFunction = newActivationFunction; }
	Function* getActivationFunction() { return activationFunction; }
	virtual Function* Active()override;
	virtual Function* Hover()override;
	virtual Function* Inactive()override;
	void render(sf::RenderTarget* target)override;
};