#include "pch.h"

Layer::Layer(std::vector <Object*> & objectsPreview)
{
	objects = objectsPreview;
}

Layer::Layer(std::vector <Object*> * objectsPreview)
{
	objects = *objectsPreview;
}

void Layer::draw(sf::RenderWindow & window)
{
	for (const auto & k : objects) k->draw(window);
}

void Layer::draw(sf::RenderWindow& window, sf::View& view, float zoom)
{
	for (const auto & k : objects) k->draw(window, view, zoom);
}

void Layer::addObject(Object* newObject)
{
	objects.push_back(newObject);
}

void Layer::addObject(Object& newObject)
{
	objects.push_back(&newObject);
}

unsigned Layer::getSize() const
{
	unsigned objectsSize = size_tToInt(objects.size());
	return objectsSize;
}

Engine::Engine()
{
	currentlySelectedObject = nullptr;
	currentlySelectedInterface = nullptr;
	globalMap = nullptr;
	deltaTime = 0;
	mapPointer = nullptr;
	event.type = sf::Event::Count;

	renderObjects.resize(100);

	logFile.open("Engine.log", std::ios::out);
	theGame.create(sf::VideoMode(1280U, 720U), "Emiriusu", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	Layers.push_back(new Layer);
	interfaceLayers.push_back(new InterfaceLayer);
	gameScreen.setSize(1280.0f, 720.0f);
	gameInterface.setSize(1280.0f, 720.0f);
	theGame.setView(gameScreen);
	gameScreen.zoom(data.Settings().getZoom());
}

Engine::~Engine()
{
	Layers.clear();
	logFile.close();
}

Engine& Engine::getInstance()
{
	static Engine instance;
	return instance;
}

void Engine::refreshWindow()
{
	sf::Vector2u size = theGame.getSize();
	gameScreen.setSize(float(size.x), float(size.y));
	gameInterface.setSize(float(size.x), float(size.y));
}

void Engine::draw() const
{
	for (const auto& i : Layers)
	{
		i->draw(theGameR, gameScreenR, Engine::getInstance().getData().Settings().getZoom()); /// ???
	}
}

void Engine::drawInterface() const
{
	for (const auto& i : interfaceLayers)
	{
		i->render(theGameP);
	}
}

void Engine::addLayer(Layer* newLayer)
{
	Layers.push_back(newLayer);
}

void Engine::addLayer(Layer& newLayer)
{
	Layers.push_back(&newLayer);
}

void Engine::addLayer(std::vector<Object*> & newLayer)
{
	Layer *temp = new Layer(newLayer);
	Layers.push_back(temp);
}

void Engine::addToLayer(Object& newObject, unsigned index)
{
	unsigned siz = size_tToInt(Layers.size()) - 1;
	if (index > siz) Log::newLog ("Podano nieprawid³owy indeks warstwy!");
	index = std::min(index, siz);
	Layers[index]->addObject(newObject);
}

void Engine::addToLayer(Object* newObject, unsigned index)
{
	unsigned siz = size_tToInt(Layers.size()) - 1;
	if (index > siz) Log::newLog("Podano nieprawid³owy indeks warstwy!");
	index = std::min(index, siz);
	Layers[index]->addObject(newObject);
}

void Engine::addToTopLayer(Object& newObject)
{
	if(!Layers.empty()) Layers.back()->addObject(newObject);
}

void Engine::addToTopLayer(Object* newObject)
{
	if (!Layers.empty()) Layers.back()->addObject(newObject);
}

void Engine::increaseNumberOfLayers()
{
	Layers.push_back(new Layer);
}

void Engine::addInterfaceLayer(InterfaceLayer* newLayer)
{
	interfaceLayers.push_back(newLayer);
}

void Engine::addInterfaceLayer(InterfaceLayer& newLayer)
{
	interfaceLayers.push_back(&newLayer);
}

void Engine::addInterfaceLayer(std::vector<Interface*>& newInterfaceLayer)
{
	InterfaceLayer* temp = new InterfaceLayer(newInterfaceLayer);
	interfaceLayers.push_back(temp);
}

void Engine::addToInterfaceLayer(Interface& newObject, unsigned index)
{
	unsigned siz = static_cast<unsigned>(interfaceLayers.size()) - 1;
	if (index > siz) Log::newLog("Podano nieprawid³owy indeks warstwy!");
	index = std::min(index, siz);
	interfaceLayers[index]->addElement(newObject);
}

void Engine::addToInterfaceLayer(Interface* newObject, unsigned index)
{
	unsigned siz = static_cast<unsigned>(Layers.size()) - 1;
	if (index > siz) Log::newLog("Podano nieprawid³owy indeks warstwy!");
	index = std::min(index, siz);
	interfaceLayers[index]->addElement(newObject);
}

void Engine::addToTopInterfaceLayer(Interface& newObject)
{
	if (!interfaceLayers.empty()) interfaceLayers.back()->addElement(newObject);
}

void Engine::addToTopInterfaceLayer(Interface* newObject)
{
	if (!interfaceLayers.empty()) interfaceLayers.back()->addElement(newObject);
}

void Engine::increaseNumberOfInterfaceLayers()
{
	interfaceLayers.push_back(new InterfaceLayer);
}

sf::RenderWindow & Engine::getGameWindow()
{
	return theGame;
}
sf::View& Engine::getGameScreen()
{
	return gameScreen;
}

unsigned Engine::getNumberOfLayers() const { return size_tToInt(Layers.size()); }

unsigned Engine::getNumberOfInterfaceLayers() const { return static_cast<unsigned>(interfaceLayers.size()); }

Data& Engine::getData()
{
	return data;
}

Map* Engine::getGlobalMap()
{
	return globalMap;
}

void Engine::setGlobalMap(Map* newGlobalMap)
{
	globalMap = newGlobalMap;
}

void Engine::renderRenderObjects()
{
	Log::newLog("Rozpoczynam renderowania strumienia ma³ych obiektów");

	for (int i = 0; i < renderObjects.size(); i++)
	{
		if (renderObjects[i].empty()) continue;

		increaseNumberOfLayers();

		for (int j = 0; j < renderObjects[i].size(); j++) addToTopLayer(renderObjects[i][j]);
	}
}

void Engine::addToRenderObjects(Object* objToRen, unsigned selectLayer)
{
	Log::newLog("Dodaje nowy obiekt do strumienia wyœwietlania ma³ych obiektów, warstwa: " + std::to_string(selectLayer));
	renderObjects[selectLayer - 1].push_back(objToRen);
}

void Engine::deleteFormRenderObjects(Object* removalbeObj)
{
	Log::newLog("Usuwam objekt ze strumienia wyœwietlania ma³ych obiektów");

	for (int i = 0; i < renderObjects.size(); i++)
	{
		if (renderObjects[i].empty()) continue;

		for (auto it = renderObjects[i].begin(); it != renderObjects[i].end(); it++)
		{
			if (*it == removalbeObj)
			{
				renderObjects[i].erase(it);
				return;
			}
		}
	}
}

Interface* Engine::searchInterfaceLayers(sf::Vector2f mousePos)
{
	size_t t = interfaceLayers.size() - 1;

	do
	{
		std::vector <Interface*> temp = interfaceLayers[t]->getUIElements();
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp.at(i)->checkMousePoints(mousePos)) return temp.at(i);
		}

		if (t != 0) t--;
	} while (t > 0);

	return nullptr;
}

Player* Engine::createNewPlayer(std::string nickName, int AIType, std::string fraction)
{
	Player* tempPlayer = new Player;
	
	tempPlayer->setNickName(nickName);
	tempPlayer->setAIType(AIType);
	try
	{
		tempPlayer->setFraction(data.getFraction(fraction));
	}
	catch (std::string exception) { Log::newLog("Problem z przypisaniem frakcji: " + exception); }

	data.addPlayer(tempPlayer);

	return tempPlayer;
}

void Engine::startGame()
{
	bool mouseClick = false;
	///Debug
	//miniTile mt(data.Textures().getTexture("TokenBeatle"), 1, 1);
	//addToLayer(mt, 0);

	///Test
	//theGame.setFramerateLimit(60);

	theGame.setVerticalSyncEnabled(true);

	Map map(data.World().getMapSize());
	setGlobalMap(&map);

	///testowi gracze
	Player* currentPlayer = createNewPlayer("Player1", 0, "Borsuki");
	Player* otherPlayer = createNewPlayer("Player2", 0, "Kuny");

	///testowe obiekty
	try
	{
		std::pair <short, short> c1 = std::make_pair(2, 2);
		std::pair <short, short> c2 = std::make_pair(3, 2);
		currentPlayer->createCity(c1);
		currentPlayer->createCity(c2);

		currentPlayer->createBuilding(c1, std::make_pair(1, 1), std::string("Shop"));
		currentPlayer->createBuilding(c1, std::make_pair(2, 2), "Shop");
		currentPlayer->createBuilding(c1, std::make_pair(1, 2), "Shop");
		currentPlayer->createBuilding(c1, std::make_pair(0, 2), "Shop");

		currentPlayer->createBuilding(c2, std::make_pair(0, 2), "Shop");
		currentPlayer->createBuilding(c2, std::make_pair(1, 2), "Shop");

		currentPlayer->deleteBuilding(c2, std::make_pair(0, 2));

		currentPlayer->createBuilding(c2, std::make_pair(0, 2), "Church");

		currentPlayer->createArmy(sf::Vector2i(map.test1.first, map.test1.second), "Army1");
		otherPlayer->createArmy(sf::Vector2i(map.test2.first, map.test2.second), "Army1");
	}
	catch (std::string exception) { Log::newLog("Napotkano wyj¹tek: " + exception); }
	
	mapOverlay world;
	world.setTileSet(data.Textures().getTileSet("biomes"));
	world.setType(0);
	addToLayer(world, 0);

	increaseNumberOfLayers();
	mapOverlay riverOverlay;
	riverOverlay.setTileSet(data.Textures().getTileSet("rivers"));
	riverOverlay.setType(1);
	addToLayer(riverOverlay, 1);

	//Button* guzik;
	//guzik=new Button(400,400,200,150,,,,);

	renderRenderObjects();

	Button* button1;
	button1 = new Button(400.0f, 400.0f, 200.0f, 150.0f, "napis");

	int x = 0, y = 0;

	while (theGame.isOpen())
	{
		sf::Vector2f mousePos = theGame.mapPixelToCoords(sf::Mouse::getPosition(theGame));

		if (currentlySelectedInterface == nullptr)
		{
			currentlySelectedInterface = searchInterfaceLayers(mousePos);
			if (currentlySelectedInterface != nullptr)
			{
				currentlySelectedInterface->Hover();
			}
		}
		else
		{
			Interface* temp = searchInterfaceLayers(mousePos);
			if (temp == nullptr || temp != currentlySelectedInterface)
			{
				currentlySelectedInterface->Inactive();
				currentlySelectedInterface = temp;
			}
		}

		deltaTime = clock.restart().asSeconds();
		//std::cerr << 1 / deltaTime << "\n";
		while (theGame.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				theGame.close();
				break;
			}
			case sf::Event::Resized:
			{
				refreshWindow();
				break;
			}
			}
		}
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta < 0)
			{
				data.Settings().increaseZoom(0.25f);
			}
			else if (event.mouseWheelScroll.delta > 0)
			{
				data.Settings().increaseZoom(-0.25f);
			}
			event.mouseWheelScroll.delta = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameScreen.move(-1000.0f * deltaTime * data.Settings().getZoom(), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			gameScreen.move(0, 1000.0f * deltaTime * data.Settings().getZoom());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gameScreen.move(0, -1000.0f * deltaTime * data.Settings().getZoom());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameScreen.move(1000.0f * deltaTime * data.Settings().getZoom(), 0);
		}
		//test sterowania
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (currentlySelectedInterface != nullptr)
				{
					currentlySelectedInterface->Click();
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2f position = theGame.mapPixelToCoords(sf::Mouse::getPosition(theGame));
			x = int(position.x) / tileResolution;
			y = int(position.y) / tileResolution;
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				if (currentlySelectedObject != nullptr)
				{	
					Army* temp = (Army*)currentlySelectedObject;
					if (temp->move(sf::Vector2i(x, y), map))
					{
						map.getTile(temp->getPosition())->ereaseSelectable();
						temp->setPosition(sf::Vector2i(x, y));
						map.getTile(x, y)->addSelectable(temp);
					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (currentlySelectedInterface != nullptr)
				{
					currentlySelectedInterface->Active();
					currentlySelectedInterface->Hover();
				}
				else if (currentlySelectedObject != map.getTile(x, y)->getSelectable())
				{
					if (currentlySelectedObject != nullptr)
						currentlySelectedObject->onDeselect();
					currentlySelectedObject = map.getTile(x, y)->getSelectable();
					if (currentlySelectedObject != nullptr)
						currentlySelectedObject->onSelect();
				}
			}
		}
		//std::cout << currentlySelectedObject << std::endl;
		/*
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (!mouseClick)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i pixelCoords = sf::Mouse::getPosition(theGame);
					sf::Vector2f position = theGame.mapPixelToCoords(pixelCoords);

					x = int(position.x) / tileResolution;
					y = int(position.y) / tileResolution;

					mouseClick = true;
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (mouseClick)
				{
					std::cout << "Tile cords: " << x << ", " << y << '\n';
					if (x >= 0 && y >= 0 && x < getData().World().getMapSize() && y < getData().World().getMapSize())
					{
						std::cout << map.getTile(x, y)->getType()->getName() << '\n';
						if (map.getTile(x, y)->getArmy() != nullptr) std::cout << "Natrafiono na klikalny obiekt!\n";
						{
							if (currentlySelectedObject == nullptr) currentlySelectedObject = map.getTile(x, y)->getArmy();
						}
						if (currentlySelectedObject != nullptr)
						{
							Army* temp = (Army*)currentlySelectedObject;
							std::cout << temp->move(sf::Vector2i(x, y), map) << "\n";
							if (temp->move(sf::Vector2i(x, y), map))
							{
								temp->setPosition(sf::Vector2i(x, y));
								map.getTile(x, y)->setArmy(temp);
							}
						}
					}
					mouseClick = false;
				}
			}
		}*/
		theGame.clear();
		theGame.setView(getGameScreen());
		draw();
		theGame.setView(gameInterface);
		drawInterface();
		theGame.display();
	}
}



