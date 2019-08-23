#pragma once
#include "pch.h" 
#include "Selectable.h"

class Button : public Interface
{
	Function* activationFunction;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text textContainer;
	sf::Color idlecolor;
	sf::Color activecolor;
	sf::Color hovercolor;

	const float X, Y, WIDTH, HEIGHT;

public:
	Button(float x, float y, float width, float height, sf::RectangleShape shape, sf::Font font, sf::Text text, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor);
	Button(float x, float y, float width, float height, std::string text);

	~Button();
	void setActivationFunction(Function* newActivationFunction) { activationFunction = newActivationFunction; }

	Function* getActivationFunction() { return activationFunction; }

	Function* Active() override;
	Function* Hover() override;
	Function* Inactive() override;
	Function* Click() override;

	void render(sf::RenderTarget* target) override;
	void render(sf::RenderWindow* window) override;

	bool checkMousePoints(sf::Vector2f pos) override;
};