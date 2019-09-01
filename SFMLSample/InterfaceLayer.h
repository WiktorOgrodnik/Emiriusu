#pragma once
#ifndef INTERFACELAYER_H
#define INTERFACELAYER_H

#include "pch.h"

class Function;

class InterfaceLayer : public Interface
{
private:

	std::vector <Interface*> UIElements;

public:

	InterfaceLayer(std::vector<Interface*>& interfacePreview);
	InterfaceLayer(std::vector<Interface*>* interfacePreview);
	InterfaceLayer();

	void render(sf::RenderTarget* target) override;
	void render(sf::RenderWindow* window) override;

	void addElement(Interface* newElement);
	void addElement(Interface& newElement);

	std::vector <Interface*> getUIElements();

	unsigned short getSize() const;

	Function* Active() override;
	Function* Hover() override;
	Function* Inactive() override;
	Function* Click() override;

	bool checkMousePoints(sf::Vector2f pos) override { return false; }
};

#endif /* INTERFACELAYER_H */

