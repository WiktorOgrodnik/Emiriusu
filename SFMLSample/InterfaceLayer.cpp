#include "pch.h"
#include "InterfaceLayer.h"

InterfaceLayer::InterfaceLayer(std::vector <Interface*>* interfacePreview)
{
	UIElements = *interfacePreview;
}

InterfaceLayer::InterfaceLayer(std::vector <Interface*>& interfacePreview)
{
	UIElements = interfacePreview;
}

InterfaceLayer::InterfaceLayer()
{

}

void InterfaceLayer::render(sf::RenderTarget* target)
{
	for (const auto& i : UIElements) i->render(target);
}

void InterfaceLayer::render(sf::RenderWindow* window)
{
	for (const auto& i : UIElements) i->render(window);
}

void InterfaceLayer::addElement(Interface* newElement)
{
	UIElements.push_back(newElement);
}

void InterfaceLayer::addElement(Interface& newElement)
{
	UIElements.push_back(&newElement);
}

unsigned short InterfaceLayer::getSize() const
{
	return static_cast<unsigned short>(UIElements.size());
}

Function* InterfaceLayer::Active()
{
	return nullptr;
}

Function* InterfaceLayer::Hover()
{
	return nullptr;
}

Function* InterfaceLayer::Inactive()
{
	return nullptr;
}

Function* InterfaceLayer::Click()
{
	return nullptr;
}

std::vector <Interface*> InterfaceLayer::getUIElements()
{
	return UIElements;
}

