#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "pch.h"
#include "Object.h"
#include "Data.h"

class Layer : public Object
{
private:

	std::vector <Object*> objects; /// obiekty na warstwie

public:

	Layer(std::vector <Object*> & objectsPreview); /// konstruktor (przyjmuje referencjê na wektor obiektów)
	Layer(std::vector <Object*> * objectsPreview); /// konstruktor (przyjmuje wskaŸnik na wektor obiektów)
	Layer() {}

	void draw(sf::RenderWindow & window) override; /// funkcja rysuje warstwê na erkanie
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// funkcja rysuje warstwê na erkanie (tylko mapa u¿ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override {}
	void addObject(Object* newObject); /// dodaj obiekt do warstwy (przyjmuje wskaŸnik na obiekt)
	void addObject(Object& newObject); /// dodaj obieket do wartwy (przyjmuje refernecjê na obiekt)
	
	unsigned getSize() const; /// zwraca iloœæ obiektów
};

class Engine
{
private:

	std::fstream logFile; /// zmienna plikowa pliku Engine.log
	Engine(); /// konstruktor
	Engine(const Engine&); /// konstruktor
	~Engine(); /// destruktor

	Data data; /// wiêkszoœæ danych, u¿ywanych przez program
	Map* globalMap; /// Mapa globalna

	sf::RenderWindow theGame; /// okno g³owne gry
	sf::RenderWindow& theGameR = theGame; /// referencja na okno g³ówne gry
	sf::RenderWindow* theGameP = &theGame; /// wskaŸnik na okno g³ówne gry
	sf::View gameScreen; /// obecnie wyœwietlana czêœæ mapy
	sf::View gameInterface;
	sf::View& gameScreenR = gameScreen; /// referencja na obecnie wyœwietlan¹ czêœæ mapy
	sf::Clock clock; /// zegar gry
	sf::Event event; /// event okna

	float deltaTime; /// czas który up³yn¹³ od poprzedniej klatki

	Selectable* currentlySelectedObject; /// obecnie wybrana jednostka
	Interface* currentlySelectedInterface; /// obecnie wybrany element interfejsu

	std::vector<Layer*> Layers; /// wszystkie warstwy
	std::vector<InterfaceLayer*> interfaceLayers; /// wszytkie warstwy interfejsu
	std::vector <std::vector <Object*>> renderObjects; /// strumieñ ma³ych obiektów do renderowania

	void renderRenderObjects(); /// funkcja renderuje strumieñ ma³e obiekty
	void refreshWindow(); /// funkcja odœwie¿aj¹ca ekran 
	void setGlobalMap(Map* newGlobalMap); /// setter mapy globalnej
	
	Interface* searchInterfaceLayers(sf::Vector2f mousePos); /// Znajduje element interfejsu na który wskazuje myszka
	Player* createNewPlayer(std::string nickName, int AIType, std::string fraction); /// tworzy nowego gracza
	sf::Vector2f mousePosition;

	///Zablokowanie mo¿liwoœci kopiowania
	Engine operator= (const Engine& other);

public:

	static Engine & getInstance(); /// funkcja przekazuj¹ca referencjê na instancjê silnika
	void* mapPointer; /// wskaŸnik na mapê (funckjonalnoœæ przestarza³a)

	void draw() const; /// rysuje wszytkie warstwy po kolei
	void drawInterface() const; /// rysuje wszystkie warstwy interfejsu

	void addLayer(Layer* newLayer); /// dodaje warstwe (przyjmuje wskaŸnik na warstwê)
	void addLayer(Layer& newLayer); /// dodaje warstwê (przyjmuje referencjê na warstwê)
	void addLayer(std::vector<Object*> & newLayer); /// dodaje warstwê (przyjmuje referncjê na wektor obiektów)
	void addToLayer(Object& newObject, unsigned index); /// dodaje obiekt do wybranej warstwy
	void addToLayer(Object* newObject, unsigned index); /// dodaje obiekt do wybranej warstwy
	void addToTopLayer(Object& newObject); /// dodaje obiekt do najwy¿szej warstwy
	void addToTopLayer(Object* newObject); /// dodaje obiekt do najwy¿szej warstwy
	void increaseNumberOfLayers(); /// zwiêksza liczbê warstw o jedn¹

	void addInterfaceLayer(InterfaceLayer* newLayer); /// dodaje warstwe interfejsu (przyjmuje wskaŸnik na warstwê)
	void addInterfaceLayer(InterfaceLayer& newLayer); /// dodaje warstwê interfejsu (przyjmuje referencjê na warstwê)
	void addInterfaceLayer(std::vector<Interface*>& newLayer); /// dodaje warstwê interfejsu (przyjmuje referncjê na wektor obiektów)
	void addToInterfaceLayer(Interface& newObject, unsigned index); /// dodaje obiekt do wybranej warstwy interfejsu
	void addToInterfaceLayer(Interface* newObject, unsigned index); /// dodaje obiekt do wybranej warstwy interfejsu
	void addToTopInterfaceLayer(Interface& newObject); /// dodaje obiekt do najwy¿szej warstwy interfejsu
	void addToTopInterfaceLayer(Interface* newObject); /// dodaje obiekt do najwy¿szej warstwy interfejsu
	void increaseNumberOfInterfaceLayers(); /// zwiêksza liczbê warstw interfejsu o jedn¹

	void startGame(); /// uruchamia silnik

	///GameWindows access functions:
	sf::RenderWindow& getGameWindow(); /// funkcja zwraca referencjê na okno gry
	sf::View& getGameScreen(); /// funkcja zwraca referencjê na obecnie wyœwietlan¹ czêœæ mapy
	
	unsigned getNumberOfLayers() const; /// zwraca iloœæ warstw
	unsigned getNumberOfInterfaceLayers() const; /// zwraca iloœæ warstw interfejsu

	Data& getData(); /// zwraca referencjê na klasê data
	Map* getGlobalMap(); /// zwraca mapê globaln¹

	void addToRenderObjects(Object* selToObj, unsigned selectLayer); /// dodaj obiekt klasy Object do strumienia ma³ych obiektów do renderowania
	void deleteFormRenderObjects(Object* removableObj); /// usuwa dany obiekt klasy Object ze strumienia ma³ych obiektów do renderowania

	sf::Vector2f getMousePosition() { return mousePosition; }
};

#endif /* ENGINE_H */