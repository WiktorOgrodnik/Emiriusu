#include "pch.h"
#include "Button.h"


Button::Button(float x, float y, float width, float height, sf::RectangleShape shape, sf::Font font, sf::Text text, sf::Color idlecolor, sf::Color hovercolor, sf::Color activecolor) : X(x), Y(y), WIDTH(width), HEIGHT(height)
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

Button::Button(float x, float y, float width, float height, std::string text_) : X(x), Y(y), WIDTH(width), HEIGHT(height)
{
	if (!font.loadFromFile("C:/windows/fonts/arial.ttf"))
	{
		Log::newLog("Nie uda³o siê za³adowaæ czcionki arial.ttf");
	}

	textContainer.setString(text_);
	textContainer.setFont(font);
	textContainer.setCharacterSize(14);
	textContainer.setPosition(x + width/2, y + height/2);
	textContainer.setFillColor(sf::Color::White);

	sf::FloatRect textBounds = textContainer.getLocalBounds();

	shape.setPosition(sf::Vector2f(x, y));
	shape.setFillColor(sf::Color(102, 102, 102));
	shape.setSize(sf::Vector2f(width, height));

	Engine::getInstance().addToInterfaceLayer(this, 0);

	idlecolor = sf::Color(102, 102, 102);
	activecolor = sf::Color(92, 92, 92);
	hovercolor = sf::Color(112, 112, 112);
}

Button::~Button()
{
}

Function* Button::Active()
{
	return nullptr;
}

Function* Button::Hover()
{
	shape.setFillColor(sf::Color(hovercolor));
	return nullptr;
}

Function* Button::Inactive()
{
	shape.setFillColor(sf::Color(idlecolor));
	return nullptr;
}

Function* Button::Click()
{
	shape.setFillColor(sf::Color(activecolor));
	return nullptr;
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(shape);
	window->draw(textContainer);
}

bool Button::checkMousePoints(sf::Vector2f pos)
{
	//std::cerr << "POS.X: " << pos.x << " POS.Y: " << pos.y << '\n';
	//std::cerr << "X: " << X << " Y: " << Y << '\n';

	if (pos.x >= X && pos.x <= X + WIDTH && pos.y >= Y && pos.y <= Y + HEIGHT)
	{
		//std::cerr << "Wykryto obiekt\n";
		return true;
	}
	else return false;
}
