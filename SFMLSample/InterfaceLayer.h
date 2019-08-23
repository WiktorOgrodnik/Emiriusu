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

	virtual Function* Active() override;
	virtual Function* Hover() override;
	virtual Function* Inactive() override;

	bool checkMousePoints(sf::Vector2f pos) override { return false; }
};

#endif /* INTERFACELAYER_H */

