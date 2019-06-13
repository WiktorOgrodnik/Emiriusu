#pragma once
class mapOverlay : public Object
{
private:
	/// Mo¿e vertex array?
	sf::Texture tileSetTexturePointer;
	sf::Texture* tileSet;
	std::vector<std::vector<sf::Vector2<char>>> generationInfo; /// 

	char type;

public:

	mapOverlay(std::vector<std::vector<sf::Vector2<char>>>& generationInfo) : generationInfo(generationInfo) {}
	mapOverlay();
	~mapOverlay();

	void draw(sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override;
	void draw(sf::RenderTexture& texture) override;

	void setTileSet(sf::Texture* newTileSet);
	void setType (char newType);
};

