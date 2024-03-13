#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "platformExample.h"
#include <string>
#include <iostream>


class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();

private:
	// Default variables for level class.
	platformExample* tiles;
	sf::Text text;
	sf::Font font;
	int currentVal;
	sf::Texture previewTexture;
	GameObject previewTile;
	GameObject areaBG;
};