#include "pch.h"

mapOverlay::mapOverlay()
{
	tileSet = nullptr;
	type = 0;
}

mapOverlay::~mapOverlay()
{
}

void mapOverlay::draw(sf::RenderWindow & window)
{
}

void mapOverlay::draw(sf::RenderWindow & window, sf::View & view, float zoom)
{
	sf::VertexArray quads;
	sf::VertexArray Quads;
	sf::Vector2f position = view.getCenter();
	sf::Vector2f size = view.getSize();
	Map* map = (Map*)Engine::getInstance().mapPointer;

	position.x -= size.x / 2.0f;
	position.y -= size.y / 2.0f;

	sf::Vector2i firstTileIndex;
	int maxIndex = Engine::getInstance().getData().World().getMapSize() - 1;

	firstTileIndex.x = std::min(std::max((int)round(position.x) / tileResolution, 0), maxIndex);
	firstTileIndex.y = std::min(std::max((int)round(position.y) / tileResolution, 0), maxIndex);

	sf::Vector2i lastTileIndex;

	lastTileIndex.x = std::min(std::max((int)round(position.x + size.x) / tileResolution, 0), maxIndex);
	lastTileIndex.y = std::min(std::max((int)round(position.y + size.y) / tileResolution, 0), maxIndex);

	Quads.setPrimitiveType(sf::Quads);
	Quads.resize(((lastTileIndex.x - firstTileIndex.x + 1) * (lastTileIndex.y - firstTileIndex.y + 1)) * 4);

	for (int i = firstTileIndex.x; i <= lastTileIndex.x; i++)
	{
		for (int j = firstTileIndex.y; j <= lastTileIndex.y; j++)
		{
			char textureXCoord = map->getMapOverlayData(i, j, 0, type);
			char textureYCoord = map->getMapOverlayData(i, j, 1, type);
			if (textureXCoord == 0) continue;

			sf::Vertex* quad = &Quads[((j - firstTileIndex.y) * (lastTileIndex.x - firstTileIndex.x + 1) + (i - firstTileIndex.x)) * 4];
			quad[0].position = sf::Vector2f(i * tileResolution, j * tileResolution);
			quad[1].position = sf::Vector2f((i + 1) * tileResolution, j * tileResolution);
			quad[2].position = sf::Vector2f((i + 1) * tileResolution, (j + 1) * tileResolution);
			quad[3].position = sf::Vector2f(i * tileResolution, (j + 1) * tileResolution);

			quad[0].texCoords = sf::Vector2f(tileResolution * (textureXCoord - 1), tileResolution * textureYCoord);
			quad[1].texCoords = sf::Vector2f(tileResolution * (textureXCoord), tileResolution * textureYCoord);
			quad[2].texCoords = sf::Vector2f(tileResolution * (textureXCoord), tileResolution * (textureYCoord + 1));
			quad[3].texCoords = sf::Vector2f(tileResolution * (textureXCoord - 1), tileResolution * (textureYCoord + 1));

		}
	}

	window.draw(Quads, tileSet);
}

void mapOverlay::draw(sf::RenderTexture & texture)
{

}

void mapOverlay::setTileSet(sf::Texture* newTileSet)
{
	tileSet = newTileSet;
}

void mapOverlay::setType(char newType)
{
	type = newType;
}
