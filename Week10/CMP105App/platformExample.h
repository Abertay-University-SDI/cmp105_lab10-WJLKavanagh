#pragma once
#include "Framework/TileMap.h"

#include <string>

class platformExample : public TileMap
{
public:
	platformExample(const std::string& fName);

	std::vector<int> loadFromFile(const std::string & fName);
	void writeToFile(const std::string & fName);
	void updateTile(sf::Vector2u pos, int val);
	const sf::Texture* getTileTexture(int v);

	
};

