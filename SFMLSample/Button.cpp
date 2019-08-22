#include "pch.h"
#include "Button.h"


Button::Button(float x, float y, float width, float height, sf::RectangleShape shape, sf::Font font, sf::Text text, sf::Color idlecolor, sf::Color activecolor)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color(idlecolor));
	//to do tekstu w guzikach
	//text.setCharacterSize(14);
	//text.setString(text);
	//text.setPosition();
	//text.setFillColor(sf::Color::White);
}

Button::~Button()
{
}

Function* Button::onSelect()
{
	shape.setFillColor(sf::Color(activecolor));
	return nullptr;
}

Function* Button::onClick()
{
	return nullptr;
}

Function* Button::onDeselect()
{
	shape.setFillColor(sf::Color(idlecolor));
	return nullptr;
}